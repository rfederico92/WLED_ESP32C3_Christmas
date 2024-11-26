@ECHO OFF
ECHO Merry Christmas! Love Ron of FrequencyLabs
esptool erase_flash
esptool write_flash 0x0000 bootloader.bin 0x8000 partitions.bin 0xe000 "%HOMEDRIVE%%HOMEPATH%\.platformio\packages\framework-arduinoespressif32\tools\partitions\boot_app0.bin" 0x10000 firmware.bin
ECHO Enjoy!
PAUSE