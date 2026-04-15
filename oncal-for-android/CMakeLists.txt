cmake_minimum_required(VERSION 3.16)

project(_Oncall_ VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(_Oncall_
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        about.h about.cpp about.ui
        add_req.h add_req.cpp add_req.ui
        sources.qrc
        search.h search.cpp search.ui
        android/AndroidManifest.xml android/build.gradle android/res/values/libs.xml
        terms.h terms.cpp terms.ui
    )
else()
    if(ANDROID)
        add_library(_Oncall_ SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(_Oncall_
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(_Oncall_ PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network)

# --- START: The Real Final Corrected OpenSSL section ---
if(ANDROID)
    # 1. مسار مجلد include لم يتغير
    set(OPENSSL_INCLUDE_PATH "C:/Qt/android_openssl-master/include")

    # 2. المسار الأساسي لمجلدات المكتبات (ssl_3)
    set(OPENSSL_LIBS_BASE_PATH "C:/Qt/android_openssl-master/ssl_3")

    # 3. إضافة مسار الـ headers
    target_include_directories(_Oncall_ PRIVATE ${OPENSSL_INCLUDE_PATH})

    # 4. **الحل النهائي:** نربط مباشرة بالمسار الكامل للملفات الحقيقية
    # هذا يخبر CMake بتجاهل الملفات الصغيرة واستخدام الملفات الكبيرة مباشرة
    target_link_libraries(_Oncall_ PRIVATE
        "${OPENSSL_LIBS_BASE_PATH}/${CMAKE_ANDROID_ARCH_ABI}/libssl_3.so"
        "${OPENSSL_LIBS_BASE_PATH}/${CMAKE_ANDROID_ARCH_ABI}/libcrypto_3.so"
    )

    # رسالة للتأكيد
    message(STATUS "OpenSSL libraries explicitly linked for ABI: ${CMAKE_ANDROID_ARCH_ABI}")
endif()
# --- END: The Real Final Corrected OpenSSL section ---

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example._Oncall_)
endif()
set_target_properties(_Oncall_ PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS _Oncall_
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(_Oncall_)
endif()

# --- START: Added for OpenSSL deployment ---
# هذه الخطوة مهمة لنسخ مكتبات OpenSSL مع التطبيق إلى جهاز الأندرويد
if(ANDROID)
    # تأكد من أن هذا المسار هو نفس المسار الذي استخدمته لربط المكتبات
    set(OPENSSL_LIBS_DEST_PATH "C:/Qt/android_openssl-master/ssl_3")

    # قائمة الملفات التي يجب نسخها (ملفات .so)
    set(OPENSSL_DEPLOY_LIBS
        "${OPENSSL_LIBS_DEST_PATH}/${CMAKE_ANDROID_ARCH_ABI}/libssl_3.so"
        "${OPENSSL_LIBS_DEST_PATH}/${CMAKE_ANDROID_ARCH_ABI}/libcrypto_3.so"
    )

    # نسخ المكتبات إلى مجلد lib الخاص بالتطبيق على الأندرويد
    # Qt Creator سيقوم بجمع هذه الملفات ووضعها في المكان الصحيح على الجهاز
    foreach(lib ${OPENSSL_DEPLOY_LIBS})
        get_filename_component(lib_name ${lib} NAME)
        add_custom_command(TARGET _Oncall_ POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${lib}
            "${CMAKE_CURRENT_BINARY_DIR}/android-build/libs/${CMAKE_ANDROID_ARCH_ABI}/${lib_name}"
            COMMENT "Copying OpenSSL library ${lib_name} for deployment"
        )
    endforeach()
endif()
# --- END: Added for OpenSSL deployment ---
