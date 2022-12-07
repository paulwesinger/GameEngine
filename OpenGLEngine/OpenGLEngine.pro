TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

unix:LIBS += -L /usr/lib64 -L/usr/lib64/GL -lGL -lSDL2 -lGLEW -lSDL2_image -lfreetype

SOURCES += \
        Animate/animate.cpp \
        Base/base.cpp \
        Cad/cad2d.cpp \
        base2d/base2d.cpp \
        baseobject/baseobject.cpp \
        buttons/button.cpp \
        camera/camera.cpp \
        checkbox/checkbox.cpp \
        cockpit/cockpit.cpp \
        colors/colorscheme.cpp \
        controllcontainer/controllcontainer.cpp \
        cube/colorcube.cpp \
        cube/cube.cpp \
        engine/engine.cpp \
        error/error.cpp \
        fileutils/fileutil.cpp \
        imageloader/loadimage.cpp \
        initgl.cpp \
        landscape/landscape.cpp \
        lights/light.cpp \
        logs/logs.cpp \
        main.cpp \
        menu/menu.cpp \
        meshobject/meshobject.cpp \
        objectclasses/object.cpp \
        objloader/objloader.cpp \
        particleengine/partikelengine.cpp \
        plane3D/plane3D.cpp \
        projection/projection.cpp \
        shaders/shader.cpp \
        skybox/skybox.cpp \
        sphere/sphere.cpp \
        textedit/textedit.cpp \
        textrenderer/textrender.cpp \
        utils/utils.cpp \
        vecmath/vecmath.cpp \
        window/window.cpp
HEADERS += \
            Animate/animate.h \
            Base/base.h \
            Cad/cad2d.h \
            base2d/base2d.h \
            baseobject/baseobject.h \
            buttons/button.h \
            camera/camera.h \
            checkbox/checkbox.h \
            cockpit/cockpit.h \
            colors/colorscheme.h \
            controllcontainer/controllcontainer.h \
            cube/colorcube.h \
            cube/cube.h \
            defaults.h \
            defines.h \
            engine/engine.h \
            error/error.h \
            fileutils/fileutil.h \
            functions.h \
            imageloader/loadimage.h \
            initgl.h \
            landscape/landscape.h \
            lights/light.h \
            logs/logs.h \
            menu/menu.h \
            meshobject/meshobject.h \
            objectclasses/object.h \
            objloader/objloader.h \
            particleengine/partikelengine.h \
            plane3D/plane3D.h \
            projection/projection.h \
            shaders/shader.h \
            skybox/skybox.h \
            sphere/sphere.h \
            textedit/textedit.h \
            textrenderer/textrender.h \
            utils/utils.h \
            vecmath/vecmath.h \
            window/window.h
