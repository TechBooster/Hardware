# C91 GameKit 

TechBooster's original hardware  (Arduino Compatible / Pro mini ATMEGA 328T 3.3V/8MHz)

# C91 GameKit 

## �f�B���N�g���\��

 * c91-gamekit-hardware-design ��e��DXF�f�[�^
 * c91-gamekit-software �v���C���X�g�[���\�t�g�E�F�A�u���Ƃ��Ȃ��V���v�T���v���\�[�X�R�[�h

## �J����

 * �n�[�h�E�F�A
   * SeeedStudio Arduino Pro Mini 3.3V/8MHz
   * 1.44" SPI LCD
   * FT232RL�{�[�h(�������ݗp)
 * �\�t�g�E�F�A
 * Visual Studio 2015 Professional(Community�ł��AExpress�s��)
   * [VisualMicro](https://marketplace.visualstudio.com/items?itemName=VisualMicro.ArduinoIDEforVisualStudio)�g�����K�{
 * Arduino IDE��1.6.12�œ���m�F�ς�

## �^�C�g����ʂق��摜�f�[�^(xbm_*.h)�̃r���h���@�i�����ŉ摜��ύX����Ƃ��ɕK�v�Ȏ菇�j

1. artwork�f�B���N�g���ȉ���PNG�t�H�[�}�b�g�ŏ����Ώۃt�@�C�����i�[

2. artwork/dimension.csv �t�@�C���Ƀt�@�C����(.png������)�Ɛ��@���L��(�ق��̃t�@�C���̋L�q�ɕ키)

3. ImageMagick�𓱓�����Mac��(Bash on Windows�ł���)�Ŏ��̃R�}���h�����s

```
$ ./generate_artwork_headers.sh
```

���̂悤�Ɏ��s���ʂ��o�͂����ΐ����B

```
INFO: Input image "body.png" need to be 20 x 42
INFO: Successfully written xbm_body.h
INFO: Input image "hand-left-1.png" need to be 22 x 25
INFO: Successfully written xbm_hand_left_1.h
INFO: Input image "hand-left-2.png" need to be 22 x 34
INFO: Successfully written xbm_hand_left_2.h
...
INFO: Input image "title.png" need to be 64 x 64
INFO: Successfully written xbm_title.h
```

4. Arduino IDE��Visual Studio��Ńv���W�F�N�g���r���h�������΃Q�[���{�̂ɔ��f�����(�͂�)