#include <Arduino.h>
#include <LittleFS.h>
// #include <SPIFFS.h>
// #include <FFat.h>
#include <time.h>

#define LFS_FORMAT_ON_FAIL true
#define LFS_BASEPATH "/littlefs"
#define LFS_MAXOPENFILES 32U
#define LFS_PARTITIONLABEL "data"

void listDir(fs::FS &fs, const char * dirname);

void setup() {


    if (!LittleFS.begin(LFS_FORMAT_ON_FAIL, LFS_BASEPATH, LFS_MAXOPENFILES, LFS_PARTITIONLABEL)) {
        log_e("littlefs begin failed");
    } else {
        log_i("littlefs begin succeeded");
    };

    listDir(LittleFS, "/");
    log_i("all done");
}

void loop() {

}

void listDir(fs::FS &fs, const char * dirname){
    log_i("listing dir: %s", dirname);

    File root = fs.open(dirname);
    log_i("root: %s", root.name());

    if(!root){
        log_e("- failed to open root dir");
        return;
    }
    if(!root.isDirectory()){
        log_e(" - root is not a directory");
        return;
    }

    File file = root.openNextFile();

    while(file){
        
        if(file.isDirectory()){
            log_i("d- %s", file.name());

            // Serial.print(file.name());
            // time_t t= file.getLastWrite();
            // struct tm * tmstruct = localtime(&t);
            // Serial.printf("  LAST WRITE: %d-%02d-%02d %02d:%02d:%02d\n",(tmstruct->tm_year)+1900,( tmstruct->tm_mon)+1, tmstruct->tm_mday,tmstruct->tm_hour , tmstruct->tm_min, tmstruct->tm_sec);


            } else {
            log_i("f- %s %i", file.name(), file.size());

            // time_t t= file.getLastWrite();
            // struct tm * tmstruct = localtime(&t);
            // Serial.printf("  LAST WRITE: %d-%02d-%02d %02d:%02d:%02d\n",(tmstruct->tm_year)+1900,( tmstruct->tm_mon)+1, tmstruct->tm_mday,tmstruct->tm_hour , tmstruct->tm_min, tmstruct->tm_sec);

        }

        file = root.openNextFile();
    }
}