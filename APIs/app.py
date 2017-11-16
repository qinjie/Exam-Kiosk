import json
import datetime
import pymysql
from chalice import Chalice

db_host = "iot-centre-rds.crqhd2o1amcg.ap-southeast-1.rds.amazonaws.com"
db_name = "exam_kiosk"
db_username = "root"
db_password = "Soe7014Ece"


app = Chalice(app_name="exam_kiosk")


@app.route("/seat/{rfid}")
def index(rfid):
    result = []
    conn = connect_database()
    with conn.cursor() as cur:
        cur.execute("SELECT `card`, `name`, `module`, `exam_date`, `exam_venue`, `start_time`, `end_time`, `seat_number` FROM `exam_seating` WHERE `card` = (select card from user where `rfid` = '{}')"
                                    .format(rfid))
    for row in cur:
        result.append({'card':str(row[0]),'name':str(row[1]),'module':str(row[2]),'date':str(row[3]),'venue':str(row[4]),'start_time':str(row[5]),'end_time':str(row[6]),'seat':str(row[7])})
    if result:
        return json.dumps(result)
    else:
        return json.dumps([{'success': '0', 'message':'Student not found'}])


@app.route("/user/{rfid}")
def user_info(rfid):
    result = []
    conn = connect_database()
    with conn.cursor() as cur:
        cur.execute("SELECT `card`, `name`, `email`, `role` FROM `user` WHERE `rfid` = '{}'".format(rfid))
    for row in cur:
        result.append({'card':str(row[0]), 'name':str(row[1]), 'email':str(row[2]), 'role': 'student' if int(row[3])==10 else 'staff'})
        break
    if result:
        return json.dumps(result)
    else:
        return json.dumps([{'message':'User not found'}])

@app.route("/toilet/{rfid}")
def list_toilet(rfid):
    result = []
    conn = connect_database()
    student_card = ''
    with conn.cursor() as cur:
        cur.execute("SELECT `card` FROM `user` WHERE `rfid` = '{}'".format(rfid))
    for row in cur:
        student_card = str(row[0])
        break
    with conn.cursor() as cur:
        cur.execute("SELECT `card`, `name`, `time_in`, `time_out`, `staff_card`  FROM `toilet_trip` where module = (select distinct module from exam_seating \
                    where `exam_date` = DATE_FORMAT(NOW(),'%Y-%m-%d') and `start_time` < DATE_FORMAT(NOW(),'%H:%i:%s') and `end_time`> DATE_FORMAT(NOW(),'%H:%i:%s') \
                    and `card` = '{}')".format(student_card))
    for row in cur:
        if ((str(row[0]) == student_card)):
            result.append({'card': str(row[0]), 'name': str(row[1]), 'time_in': str(row[2]), 'time_out': str(row[3]), 'staff': str(row[4]), 'sender': True})
        else:
            result.append({'card': str(row[0]), 'name': str(row[1]), 'time_in': str(row[2]), 'time_out': str(row[3]),'staff': str(row[4])})
    if result:
        return json.dumps(result)
    else:
        return json.dumps([{'message':'Student not found'}])

@app.route('/toilet', methods=['POST'])
def toilet_out():
    request = app.current_request
    data = request.json_body

    try:
        student_rfid = str(data['student_rfid'])
    except Exception as e:
        return json.dumps([{'success': '0', 'message': 'Missing Student RFID'}])

    try:
        staff_rfid = str(data['staff_rfid'])
    except Exception as e:
        return json.dumps([{'success': '0', 'message': 'Missing Staff RFID'}])

    conn = connect_database()
    student_card = ''
    student_name = ''
    module = ''
    exam_venue = ''
    staff_card = ''
    with conn.cursor() as cur:
        response = cur.execute("SELECT `card`, `name`, `module`, `exam_venue` FROM `exam_seating` WHERE `card` = (select card from user where `rfid` = '{}') \
                    and `exam_date` = DATE_FORMAT(NOW(),'%Y-%m-%d') and `start_time` < DATE_FORMAT(NOW(),'%H:%i:%s') and `end_time`> DATE_FORMAT(NOW(),'%H:%i:%s')"
                                    .format(student_rfid))
        if response == 0:
            return json.dumps([{'success':'0','message':'Student not found'}])

    for row in cur:
        student_card= str(row[0])
        student_name = str(row[1])
        module = str(row[2])
        exam_venue = str(row[3])
        break

    with conn.cursor() as cur:
        response = cur.execute("select `card` from user where `rfid` = '{}'".format(staff_rfid))
        if response == 0:
            return json.dumps([{'success':'0','message':'Staff not found'}])

    for row in cur:
        staff_card = str(row[0])
        break

    response = 0
    try:
        with conn.cursor() as cur:
            response = cur.execute("INSERT INTO `toilet_trip`(`card`, `name`, `module`, `exam_venue`, `staff_card`, `time_out`) VALUES ('{}','{}','{}','{}','{}',DATE_FORMAT(NOW(),'%H:%i:%s'))".format(student_card, student_name, module, exam_venue, staff_card))
            conn.commit()
    except Exception as e:
        return json.dumps([{'success':'0','message':'Internal Error, Insert Fail'}])

    if response > 0:
        try:
            with conn.cursor() as cur:
                cur.execute("SELECT `card`, `name`, `time_in`, `time_out`, `staff_card`  FROM `toilet_trip` where module = (select distinct module from exam_seating where `exam_date` = DATE_FORMAT(NOW(),'%Y-%m-%d') and `start_time` < DATE_FORMAT(NOW(),'%H:%i:%s') and `end_time`> DATE_FORMAT(NOW(),'%H:%i:%s'))")
            result = []
            for row in cur:
                if (str(row[0]) == student_card):
                    result.append({'card': str(row[0]), 'name': str(row[1]), 'time_in': str(row[2]), 'time_out': str(row[3]),'staff': str(row[4]), 'sender': True})
                else:
                    result.append({'card': str(row[0]), 'name': str(row[1]), 'time_in': str(row[2]), 'time_out': str(row[3]),'staff': str(row[4])})
            return json.dumps(result)
        except Exception as e:
            return json.dumps([{'success': '0', 'message': e}])
    else:
        return json.dumps([{'success': '0', 'message':'Student not found'}])


@app.route('/toilet/update', methods=['POST'])
def toilet_in():
    request = app.current_request
    data = request.json_body
    try:
        student_rfid = str(data['student_rfid'])
    except Exception as e:
        return json.dumps([{'success': '0', 'message': 'Missing Student RFID'}])

    conn = connect_database()
    toilet_id = ''
    with conn.cursor() as cur:
        cur.execute("SELECT id FROM `toilet_trip` WHERE `card` = (select `card` from `user` where `rfid` = '{}') and `time_in` is NULL"
                                    .format(student_rfid))
    for row in cur:
        toilet_id = str(row[0])
        break

    response = 0
    try:
        with conn.cursor() as cur:
            response = cur.execute("UPDATE `toilet_trip` SET `time_in` = DATE_FORMAT(NOW(),'%H:%i:%s') where `id` = {}".format(toilet_id))
            conn.commit()
    except Exception as e:
        print(e)

    if response > 0:
        try:
            with conn.cursor() as cur:
                cur.execute("SELECT `card`, `name`, `time_in`, `time_out`, `staff_card`  FROM `toilet_trip` where module = (select distinct module from exam_seating where `exam_date` = DATE_FORMAT(NOW(),'%Y-%m-%d') and `start_time` < DATE_FORMAT(NOW(),'%H:%i:%s') and `end_time`> DATE_FORMAT(NOW(),'%H:%i:%s'))")
            result = []
            for row in cur:
                result.append({'card': str(row[0]), 'name': str(row[1]), 'time_in': str(row[2]), 'time_out': str(row[3]),'staff': str(row[4])})
            return json.dumps(result)
        except Exception as e:
            return json.dumps([{'success': '0', 'message': e}])
    else:
        return json.dumps([{'success': '0', 'message':'Student not found'}])

@app.route('/submission', methods=['POST'])
def submission():
    request = app.current_request
    data = request.json_body
    try:
        student_rfid = str(data['student_rfid'])
    except Exception as e:
        return json.dumps([{'success': '0', 'message': 'Missing Student RFID'}])

    conn = connect_database()
    student_card = ''
    student_name = ''
    module = ''
    exam_venue = ''
    exam_date = ''
    start_time = ''
    with conn.cursor() as cur:
        response = cur.execute("SELECT `card`, `name`, `module`, `exam_venue`, `exam_date`, `start_time` FROM `exam_seating` WHERE `card` = (select card from user where `rfid` = '{}') \
                    and `exam_date` = DATE_FORMAT(NOW(),'%Y-%m-%d') and `start_time` < DATE_FORMAT(NOW(),'%H:%i:%s') and `end_time`> DATE_FORMAT(NOW(),'%H:%i:%s')"
                                    .format(student_rfid))
        if response == 0:
            return json.dumps([{'success': '0', 'message':'Student not found'}])
    for row in cur:
        student_card = str(row[0])
        student_name = str(row[1])
        module = str(row[2])
        exam_venue = str(row[3])
        exam_date = str(row[4])
        start_time = str(row[5])
        break

    response = 0
    try:
        with conn.cursor() as cur:
            response = cur.execute("INSERT INTO `early_submission`(`card`, `name`, `module`, `exam_venue`, `exam_date`, `start_time`, `submission_time`) VALUES ('{}','{}','{}','{}','{}','{}',DATE_FORMAT(NOW(),'%H:%i:%s'))".format(student_card, student_name, module, exam_venue, exam_date, start_time))
            conn.commit()
    except Exception as e:
        return json.dumps([{'success': '0', 'message':'The student have already Submitted'}])

    if response > 0:
        with conn.cursor() as cur:
            cur.execute("SELECT `card`, `name`, `module`, `submission_time`  FROM `early_submission` where module = (select distinct module from exam_seating where `exam_date` = DATE_FORMAT(NOW(),'%Y-%m-%d') and `start_time` < DATE_FORMAT(NOW(),'%H:%i:%s') and `end_time`> DATE_FORMAT(NOW(),'%H:%i:%s'))")
        result = []
        for row in cur:
            if ((str(row[0]) == student_card)):
                result.append({'card': str(row[0]), 'name': str(row[1]), 'module': str(row[2]), 'submission_time': str(row[3]), 'sender': True})
            else:
                result.append({'card': str(row[0]), 'name': str(row[1]), 'module': str(row[2]), 'submission_time': str(row[3])})
        return json.dumps(result)
    else:
        return json.dumps([{'success': '0', 'message':'Submit fail'}])


def connect_database():
    try:
        conn = pymysql.connect(db_host, user=db_username, passwd=db_password, db=db_name, connect_timeout=5)
    except Exception as e:
        print (e)
        conn = pymysql.connect()
    print("SUCCESS: Connection to RDS mysql instance succeeded")
    return conn