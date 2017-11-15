#include "listeningtag.h"
#include <QDebug>

extern "C" {
#include <wiringPi.h>
}

ListeningTag::ListeningTag(QObject *parent) :
    QThread(parent)
{
    qDebug() << "Creating new Thread" << QThread::currentThreadId();
}

void ListeningTag::print_hex(const uint8_t *pbtData, const size_t szBytes)
{
  size_t  szPos;

  for (szPos = 0; szPos < szBytes; szPos++) {
    qDebug() << pbtData[szPos] << "\n";
  }
}

void ListeningTag::emit_data(const uint8_t *pbtData, const size_t szBytes) {

    size_t  szPos;
    char data[8] = "";
    for (szPos = 0; szPos < szBytes; szPos++) {
        char temp[2];
        sprintf(temp, "%02x", pbtData[szPos]);
        strcat(data, temp);
        qDebug() << temp;
    }
    data[8] = '\0';
    qDebug() << data <<"\n";
    emit foundTag(QString(data));
}


void ListeningTag::run() {
//    qDebug() << "Thread Run";
//    if (wiringPiSetup() == -1) {
//        qDebug() << "Setup wire fail";
//        return;
//    }
//    pinMode(0, INPUT);
//    int prevValueBack = 0;
//    int prevValueNext = 0;
//    while(1) {
//        //qDebug() << "Running";
//        bool press = false;
//        int valueBack = digitalRead(0);
//        if (valueBack && valueBack != prevValueBack) {
//            qDebug() << "Back Press";
//            press = true;
//            emit foundTag("201720519");
//        }
//        prevValueBack = valueBack;

//        int valueNext = digitalRead(1);
//        if (valueNext && valueNext != prevValueNext) {
//            qDebug() << "Next Press";
//            press = true;
//            emit foundTag("999999999");
//        }
//        prevValueNext = valueNext;
//    }
    nfc_device *pnd;
    nfc_target nt;
    nfc_context *context;
    nfc_init(&context);
    if (context == NULL) {
      printf("Unable to init libnfc (malloc)\n");
      exit(EXIT_FAILURE);
    }
    //const char *acLibnfcVersion = nfc_version();
    //(void)argc;
    //printf("%s uses libnfc %s\n", argv[0], acLibnfcVersion);
     pnd = nfc_open(context, NULL);

    if (pnd == NULL) {
      printf("ERROR: %s\n", "Unable to open NFC device.");
      exit(EXIT_FAILURE);
    }
    if (nfc_initiator_init(pnd) < 0) {
      nfc_perror(pnd, "nfc_initiator_init");
      exit(EXIT_FAILURE);
    }

    printf("NFC reader: %s opened\n", nfc_device_get_name(pnd));
      const nfc_modulation nmMifare = {
      .nmt = NMT_ISO14443A,
      .nbr = NBR_106,
    };
    while(1) {
        if (nfc_initiator_select_passive_target(pnd, nmMifare, NULL, 0, &nt) > 0) {
          //printf("The following (NFC) ISO14443A tag was found:\n");
          //printf("       UID (NFCID%c): ", (nt.nti.nai.abtUid[0] == 0x08 ? '3' : '1'));
          //print_hex(nt.nti.nai.abtUid, nt.nti.nai.szUidLen);
            emit_data(nt.nti.nai.abtUid, nt.nti.nai.szUidLen);
        }
        sleep(2);
    }
    nfc_close(pnd);
    nfc_exit(context);
}

void ListeningTag::DoWork()
{
    qDebug() << "Thread::DoWork() in thread:" << QThread::currentThreadId();
    sleep(10);
}
