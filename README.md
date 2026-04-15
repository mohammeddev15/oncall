# OnCall
لتنزيل التطبيق للاندرويد و الويندوز 
[![Download on itch.io](https://img.shields.io/badge/Download-itch.io-fa5c5c?style=for-the-badge&logo=itchdotio)](https://mohammed45-ap.itch.io/oncall)

تطبيق توظيف فوري بدون حسابات.

## هيكل المشروع
oncall/
├── oncall-for-windows/ ← نسخة سطح المكتب
├── oncall-for-android/ ← نسخة الموبايل (فيها حل OpenSSL)
└── server/ ← API بـ Flask
## التقنيات
- **Client:** C++ / Qt 6
- **Server:** Python / Flask
- **Platforms:** Windows, Android

## التشغيل

### Windows
افتح `oncall-for-windows/OnCall.pro` في QtCreator

### Android
افتح `oncall-for-android/OnCall.pro`
> ملاحظة: لازم تضبط `QT_ANDROID_PACKAGE_SOURCE_DIR` في CMake

### السيرفر
```bash
cd server
python main.py
```
ماذا تعلمت
حل مشكلة OpenSSL على Android
فصل builds للمنصات المختلفة

##عن المطور
مطور بعمر 15 سنة من المغرب. أول مشروع full-stack.
