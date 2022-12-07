#include "engine.h"
#include "../utils/utils.h"
#include "../landscape/landscape.h"
#include "../sphere/sphere.h"

// macro
#define safeDelete(pt) \
    if (pt != nullptr) \
        delete pt;

void FxFog() {
    loginfo("TestFunc2","Fog");
}

void EngineTestFunc2() {
     loginfo("TestFunc2","Engine:: EngineTestFunc 2");
}
void EngineTestFunc3() {
    loginfo("TestFunc3","Engine:: EngineTestFunc 3");
}

void EngineTestFunc4() {
    loginfo("TestFunc4","Engine:: EngineTestFunc 4");
}

//---------------------------------
// DrawPanel
//---------------------------------
void CEngine::DrawPanel() {
    InitGL::togglePanel2D();
}

CEngine::CEngine(std::string titel) :
        InitGL(titel){
    con1                = nullptr;
    con2                = nullptr;

    txtFrameperSec      = nullptr;
    checkBoxAnimation   = nullptr;
    toogleSkyBoxBtn     = nullptr;

    cameraX             = nullptr;
    cameraY             = nullptr;
    cameraZ             = nullptr;

    _FullScreen = false;
    _ResX = SD_WIDTH;
    _ResY = SD_HEIGHT;

}
CEngine::~CEngine(){

    safeDelete (con1);
    safeDelete (con2);

    //safeDelete(fogBtn);
}

void CEngine::Done() {
    InitGL::Done();
}

void CEngine::Run() {

    initMenu();
    Init2D();
    Init3D();
    InitButtons();

    InitGL::Run();
}

// ---------------------------------------------------------------
// Place here Functons for button handler..
// ---------------------------------------------------------------

void CEngine::functoogleAnimation(bool checked) {
    InitGL::toggleAnimation();  // eigntlich startanimation..
}

void CEngine::functoogleBlend(bool checked) {
    InitGL::toggleBlend();
}

void CEngine::funcToogleSkybox() {
    renderSkybox = InitGL::toggleVal(renderSkybox);
}

void CEngine::funcFog(){
    loginfo("Fog - function");
}

void CEngine::Render(glm::mat4 cam) {

    if (renderSkybox)
        InitGL::Render(cam);
}

void CEngine::functoogleCockpit(bool checked) {
    InitGL::toogleCockpit();
}

// --------------------------------------------------------------
// Init Methods for Engines
// --------------------------------------------------------------
void CEngine::initMenu(){

    //                  |Resolution|  | Position           | width,height, colors             |
     MainMenu = new CMenu(_ResX, _ResY, 0, 0, MENU_WIDTH, MENU_HEIGHT,
                          glm::vec4(0.1,0.1,0.1,0.8), glm::vec4(0.9,0.9,0.9,1.0), InitGL::getShaderPtr());
    loginfo("Erstelle Main Menu ...... done","InitGL::InitEngineObject");

    int curr_y = 0;

    // -------------------------------------
    // Standard Menu ist in Initgl vorhanden
    // jetzt  befüllen
    //--------------------------------------
    con1 = new CControllContainer(InitGL::getShaderPtr(), MainMenu->Pos().x,
                                  MainMenu->Pos().y,
                                  MainMenu->Width(), 0);
    sSize s;
    sPoint p;
    p = con1->NextControllPos();


    toogleSkyBoxBtn = new CImageButton(_ResX, _ResY, PATH::ROOT_DIR + "images/ButtonReleased.png",
                           PATH::ROOT_DIR + "images/ToogleSkybox.png",con1->NextControllPos(),InitGL::getShaderPtr());


    toogleSkyBoxBtn->setColor(BTN_ENABLE);
    toogleSkyBoxBtn->setDisablecolor(BTN_DISABLE);
    toogleSkyBoxBtn->setSize(BTN_WIDTH,BTN_HEIGHT);
    toogleSkyBoxBtn->AddHandler(CEngine::funcToogleSkybox);
    con1->addButton(toogleSkyBoxBtn);


    MainMenu->addConatiner(con1);

    curr_y = MainMenu->CurrentY() + MENU_SPACER;

    //---------------------------------------------------
    // 2. container
    //---------------------------------------------------

    con2 = new CControllContainer(InitGL::getShaderPtr(),MainMenu->Pos().x,
                                             curr_y,
                                  MainMenu->Width(),0);

    //-----------------------------------------------------
    // Textedit:
    //-----------------------------------------------------

    //con2->addSpacer();
    s.w = MainMenu->Width() - CONTROLL::MARGIN_X ;
    s.h = CONTROLL::HEIGHT;

    p = con2->NextControllPos();
    txtFrameperSec = new TextEdit(_ResX, _ResY, PATH::ROOT_DIR + "images/ButtonReleased.png", p,s,
                                  glm::vec4(0.79, 0.99, 1.0, 1.0) , glm::vec4(0.79, 0.99, 1.0, 1.0),InitGL::getShaderPtr());


    txtFrameperSec->setColor(glm::vec4(0.79, 0.99, 1.0, 1.0));
    con2->addControll2D(txtFrameperSec);
    // add label for Frames to buildin textrender label
    txtFrameperSec->setLabel("FPS");

    //----------------------------------------------------
    // checkbox für Animation
    //----------------------------------------------------
    p = con2->NextControllPos();

    checkBoxAnimation = new CheckBox(_ResX, _ResY, PATH::ROOT_DIR + "images/ButtonReleased.png", p,s ,
                                     glm::vec4(0.79, 0.99, 1.0, 1.0), InitGL::getShaderPtr() );


    checkBoxAnimation->setColor(glm::vec4(0.79, 0.99, 1.0, 1.0));
    checkBoxAnimation->AddHandler(CEngine::functoogleAnimation);
    checkBoxAnimation->setChecked();
    con2->addControll2D(checkBoxAnimation);
    // add label for Frames to buildin textrender label
    checkBoxAnimation->setLabel("Animate");

    //----------------------------------------------------
    // checkbox für Blending
    //----------------------------------------------------
    p = con2->NextControllPos();

    checkBoxBlending = new CheckBox(_ResX, _ResY, PATH::ROOT_DIR + "images/ButtonReleased.png", p,s,
                                    glm::vec4(0.79, 0.99, 1.0, 1.0), InitGL::getShaderPtr() );


    checkBoxBlending->setColor(glm::vec4(0.79, 0.99, 1.0, 1.0));
    checkBoxBlending->AddHandler(CEngine::functoogleBlend);
    checkBoxBlending->setChecked();
    con2->addControll2D(checkBoxBlending);
    // add label for Frames to buildin textrender label
    checkBoxBlending->setLabel("Blending");

    //----------------------------------------------------
    // checkbox für Cockpit
    //----------------------------------------------------
    p = con2->NextControllPos();

    checkBoxCockpit = new CheckBox(_ResX, _ResY, PATH::ROOT_DIR + "images/ButtonReleased.png", p,s,
                                   glm::vec4(0.79, 0.99, 1.0, 1.0), InitGL::getShaderPtr() );


    checkBoxCockpit->setColor(glm::vec4(0.79, 0.99, 1.0, 1.0));
    checkBoxCockpit->AddHandler(CEngine::functoogleCockpit);
    checkBoxCockpit->setChecked();
    con2->addControll2D(checkBoxCockpit);
    // add label for Frames to buildin textrender label
    checkBoxCockpit->setLabel("Cockpit");

    // ---------------------------------------------------
    // Statusfenster(pos) von Camera:
    //----------------------------------------------------
    p = con2->NextControllPos();
    cameraX = new TextEdit(_ResX, _ResY, PATH::ROOT_DIR + "images/ButtonReleased.png", p,s,
                  glm::vec4(0.79, 0.99, 1.0, 1.0) , glm::vec4(0.79, 0.99, 1.0, 1.0), InitGL::getShaderPtr());

    cameraX->setColor(glm::vec4(0.79, 0.99, 1.0, 1.0));
    con2->addControll2D(cameraX);
    // add label for Frames to buildin textrender label
    cameraX->setLabel("Cam X");

    p = con2->NextControllPos();
    cameraY = new TextEdit(_ResX, _ResY, PATH::ROOT_DIR + "images/ButtonReleased.png", p,s
                  ,glm::vec4(0.79, 0.99, 1.0, 1.0) , glm::vec4(0.79, 0.99, 1.0, 1.0),InitGL::getShaderPtr());


    cameraY->setColor(glm::vec4(0.79, 0.99, 1.0, 1.0));
    con2->addControll2D(cameraY);
    // add label for Frames to buildin textrender label
    cameraY->setLabel("Cam Y");

    p = con2->NextControllPos();
    cameraZ = new TextEdit(_ResX, _ResY, PATH::ROOT_DIR + "images/ButtonReleased.png", p,s,
                           glm::vec4(0.79, 0.99, 1.0, 1.0) , glm::vec4(0.79, 0.99, 1.0, 1.0),InitGL::getShaderPtr());


    cameraZ->setColor(glm::vec4(0.79, 0.99, 1.0, 1.0));
    con2->addControll2D(cameraZ);
    // add label for Frames to buildin textrender label
    cameraZ->setLabel("Cam Z");

    p = con2->NextControllPos();
    camerayaw = new TextEdit(_ResX, _ResY, PATH::ROOT_DIR + "images/ButtonReleased.png", p,s,
                             glm::vec4(0.79, 0.99, 1.0, 1.0) , glm::vec4(0.79, 0.99, 1.0, 1.0), InitGL::getShaderPtr());


    camerayaw->setColor(glm::vec4(0.79, 0.99, 1.0, 1.0));
    con2->addControll2D(camerayaw);
    // add label for Frames to buildin textrender label
    camerayaw->setLabel("Cam Yaw");

    p = con2->NextControllPos();
    cameradirZ = new TextEdit(_ResX, _ResY, PATH::ROOT_DIR + "images/ButtonReleased.png", p,s,
                              glm::vec4(0.79, 0.99, 1.0, 1.0) , glm::vec4(0.79, 0.99, 1.0, 1.0), InitGL::getShaderPtr());


    cameradirZ->setColor(glm::vec4(0.79, 0.99, 1.0, 1.0));
    con2->addControll2D(cameradirZ);
    // add label for Frames to buildin textrender label
    cameradirZ->setLabel("CamDir.Z");

    p = con2->NextControllPos();
    cameradirX = new TextEdit(_ResX, _ResY, PATH::ROOT_DIR + "images/ButtonReleased.png", p,s,
                              glm::vec4(0.79, 0.99, 1.0, 1.0) , glm::vec4(0.79, 0.99, 1.0, 1.0),InitGL::getShaderPtr());

    cameradirX->setColor(glm::vec4(0.79, 0.99, 1.0, 1.0));
    con2->addControll2D(cameradirX);
    // add label for Frames to buildin textrender label
    cameradirX->setLabel("CamDir.X");

    MainMenu->addConatiner(con2);

}

void CEngine::ShowFramesPerSec() {
            TextRender * t = txtFrameperSec->getTextPtr();

    if (t != nullptr) {
        t->SetText(0,IntToString(_FramerateOut));
        t->Render();
    }
}

void CEngine::ShowCameraPos() {
    if (cameraX != nullptr) {
        TextRender * tX = cameraX->getTextPtr();
        if (tX != nullptr) {
            tX->SetText(0, FloatToString(camera->GetPos().x));
            tX->Render();
        }
    }

    if (cameraY != nullptr ) {
        TextRender * tY = cameraY->getTextPtr();
        if (tY != nullptr) {
            tY->SetText(0, FloatToString(camera->GetPos().y));
            tY->Render();
        }
    }

    if (cameraZ != nullptr) {
        TextRender * tZ = cameraZ->getTextPtr();
        if (tZ != nullptr) {
            tZ->SetText(0, FloatToString(camera->GetPos().z));
            tZ->Render();
        }
    }

    if (camerayaw != nullptr) {
        TextRender * tyaw = camerayaw->getTextPtr();
        if (tyaw != nullptr) {
            tyaw->SetText(0, FloatToString(camera->YawCameraDEG()));
            tyaw->Render();
        }
    }

    if (cameradirZ != nullptr) {
        TextRender * tdir = cameradirZ->getTextPtr();
        if (tdir != nullptr) {
            tdir->SetText(0, FloatToString(camera->GetDir().z));
            tdir->Render();
        }
    }

    if (cameradirX != nullptr) {
        TextRender * tdir = cameradirX->getTextPtr();
        if (tdir != nullptr) {
            tdir->SetText(0, FloatToString(camera->GetDir().x));
            tdir->Render();
        }
    }
}

void CEngine::Init2D() {

    //================================
    // Init 2D Objects
    // ==========y=====================

    // Testweise mal einfügen
    loginfo("============================");
    loginfo("Erstelle 2D Objekte.........");
    loginfo("============================");
    logimage("Erstelle TestIcon..........");
    base2d = new Base2D(_ResX, _ResY,PATH::ROOT_DIR + "icons/ibus-setup-hangul.png",getShaderPtr());
    base2d->setPos(500,400);


    testToolBox = new Window(_ResX, _ResY, getShaderPtr());
   // testToolBox->setWidth(400);
   // testToolBox->setHeight(80);
    testToolBox-> setPos(1000,800);
    add2Dobject(base2d);
    add2Dobject(testToolBox);
  }

void CEngine::Init3D(){

   logEmptyLine();
   loginfo("============================");
   loginfo("Erstelle 3D Objekte.........");
   loginfo("============================");

   fileUtil * fileutil = new fileUtil();
   bool ok;
   //--------------------------------------
   // loading Textured cubes
   //--------------------------------------
   ok = fileutil->readLine(OBJECT3D_CFG + "TexturedCubes/TexCubes.cfg", object3DTexturedList);
   if (ok) {
        if ( ! loadTexturedCubes() )
            logwarn("Fehler: Keine Textured Cubes gefunden oder Fehler im Pfad!");
   }
   else
       logwarn("Fehler: Datei  < config/TexCubes.cfg  > nicht gefunden !");


   //--------------------------------------
   // loading Textured Spheres
   //--------------------------------------
   ok = fileutil->readLine(SPHERE_CFG + "Spheres.cfg", objectTexturedSpheresList);
   if (ok) {
        if ( ! loadSpheres() )
            logwarn("Fehler: Keine Textured Spheres gefunden oder Fehler im Pfad!");
   }
   else
       logwarn("Fehler: Datei  < config/Spheres.cfg  > nicht gefunden !");

   // --------------------------------------
   // Landscape loading
   //---------------------------------------
   ok = fileutil->readLine(OBJECT3D_CFG + "Landscapes/Landscapes.cfg", object3DLandscapeList);
   if (ok) {
        if ( ! loadLandscape() )
            logwarn("Fehler: Keine Landscape gefunden oder Fehler im Pfad!");
   }
   else
       logwarn("Fehler: Datei  < config/Landscape.cfg  > nicht gefunden !");

   // --------------------------------------
   // Cockpit loading
   //---------------------------------------
   ok = fileutil->readLine(COCKPIT_CFG + "Cockpit.cfg", objectCockpitList);
   if (ok) {
        if ( ! loadCockpits() )
            logwarn("Fehler: Keine Cockpits gefunden oder Fehler im Verzeichnißpfad!");
   }
   else
       logwarn("Fehler: Datei  < config/Landscape.cfg  > nicht gefunden !");


   logEmptyLine() ;
   loginfo("----------------------------");
   loginfo(" Init 3D Objects ");
   loginfo("     READY");
   loginfo("----------------------------");
}


bool CEngine::loadLandscape() {
    loginfo("Lade Datei |Landscapes.cfg|","CEngine::loadLandscapes");

     // Liste mit Objekten abarbeiten :

    if (object3DLandscapeList.empty() )
        return false;

    logwarn("Anzahl der Landscapes: " + IntToString(object3DLandscapeList.size()));

    for (unsigned int i = 0; i < object3DLandscapeList.size(); i++) {

         std::string path = OBJECT3D_CFG + "Landscapes/" + object3DLandscapeList[i];

         loginfo("Erstelle Object: .......< " + path+ " >","Engine::loadLandscapes");

         fileUtil * objreader = new fileUtil;
         std::vector<std::string> objconfig;
         objreader->readLine(path, objconfig);

         if( ! objconfig.empty() ) {

             loginfo("objconfig size : " + IntToString(objconfig.size()),"Engine::loadLandScape");

             sLandscape landscape;
             if (initLandscape(landscape,objconfig)) {

                 LandScape * obj = new LandScape();
                 obj->SetColor(glm::vec4(landscape.color.x, landscape.color.y, landscape.color.z, landscape.color.w));
                 obj->Rotate(glm::vec3(landscape.trans.rotate.x, landscape.trans.rotate.y, landscape.trans.rotate.z) );
                 obj->Translate(glm::vec3(landscape.trans.translate.x, landscape.trans.translate.y, landscape.trans.translate.z));
                 obj->Scale(glm::vec3(landscape.trans.scale.x, landscape.trans.scale.y, landscape.trans.scale.z));

                 obj->setPatchX(landscape.patchX);
                 obj->setPatchZ(landscape.patchZ);
                 obj->setRasterX(landscape.rasterX);
                 obj->setRasterZ(landscape.rasterZ);

                 //----------------------------------------
                 // Add textures , if we have some
                 // ---------------------------------------
                 bool texturesok;
                 std::vector<std::string> images;
                 std::string path = landscape.textures;
                 if ( landscape.textures != "NONE" ) {

                     path = PATH::ROOT_DIR + path;
                     fileUtil fu;

                     texturesok =  fu.readLine(path, images);

                     if (texturesok)
                         obj->addTexture(images,"Engine::loadLandscape");
                     else
                         logwarn("Engine::loadScape :  konnte Textures nicht laden ! ","Engine::loadLandscape");
                 }
                 else {
                     int count = 0;

                     if (landscape.texture0 != "" ) {
                         images.push_back( PATH::ROOT_DIR + landscape.texture0);
                         count ++;
                     }

                     if (landscape.texture1 != "" ) {
                         images.push_back(PATH::ROOT_DIR + landscape.texture1);
                         count ++;
                     }

                     if (landscape.texture2 != "" ) {
                         images.push_back(PATH::ROOT_DIR + landscape.texture2);
                         count ++;
                     }

                     if (landscape.texture3 != "" ) {
                         images.push_back(PATH::ROOT_DIR + landscape.texture3);
                         count ++;
                     }

                     if (landscape.texture4 != "" ) {
                         images.push_back(PATH::ROOT_DIR + landscape.texture4);
                         count ++;
                     }

                     if (count > 0) {
                        obj->addTexture(images,"InitGL::addLandscape");
                        loginfo("added " + IntToString(count) + " Textures ", "Engine::loadLandscapes");
                     }
                     else
                         obj->SetHasTextures(false);
                 }

                 if (obj->init() ) {
                     loginfo("Landscape initialisisert ","CEngine::loadLandscape");
                     add2List(obj,LIGHT_SHADER); //)TEXTURE_SHADER
                 }
                 else
                    logwarn("Landscape wurde nicht initialisisert ","CEngine::loadLandscape");
             }
             else
                 logwarn("konnte Structure Landscape nicht initialisieren !!", "CEngine::loadLandscpae" );
                // Hier die neuen stringpart functions einbauen

             loginfo("Prepare for next Object: ","CEngine::init3D");
             logEmptyLine();
        }
    }
    return true;
}

bool CEngine::loadTexturedCubes(){

    loginfo("Lade Datei |TexCubes.cfg|","CEngine::loadTextureCubes");

     // Liste mit Objekten abarbeiten :

    if (object3DTexturedList.empty() )
        return false;

    for (unsigned int i = 0; i < object3DTexturedList.size(); i++) {

         std::string path = OBJECT3D_CFG + "TexturedCubes/" + object3DTexturedList[i];

         loginfo("Erstelle Textured Cubes: .......< " + path+ " >","Engine::loadTexturedCubes");

         fileUtil * objreader = new fileUtil;
         std::vector<std::string> objconfig;
         objreader->readLine(path, objconfig);


         if( ! objconfig.empty() ) {

             s3DStruct s3D;

             if (init3DStruct(s3D,objconfig)) {

                 CCube * obj = new CCube();
                 //obj->SetColor(glm::vec4(s3D.color.x, s3D.color.y, s3D.color.z, s3D.color.w));
                 if ( s3D.textures == "" )
                     obj->SetHasTextures( false);
                 else
                     obj->SetHasTextures( true);

                 obj->SetColor(glm::vec4(s3D.color.x, s3D.color.y, s3D.color.z, s3D.color.w));
                 obj->SetFirstTranslate( ( s3D.firstTranslate == 1) ? true: false);
                 obj->Rotate(glm::vec3(s3D.trans.rotate.x, s3D.trans.rotate.y, s3D.trans.rotate.z) );
                 obj->Translate(glm::vec3(s3D.trans.translate.x, s3D.trans.translate.y, s3D.trans.translate.z));
                 obj->Scale(glm::vec3(s3D.trans.scale.x, s3D.trans.scale.y, s3D.trans.scale.z));
                 obj->SetHasAlpha(true);
                 obj->SetFrontFace(GL_CCW);

                 //----------------------------------------
                 // Add textures , if we have some
                 // ---------------------------------------
                 bool texturesok;
                 std::vector<std::string> images;

                 std::string path = s3D.textures;
                 if ( s3D.textures != "NONE" ) {

                     path = PATH::ROOT_DIR + path;
                     fileUtil fu;

                     texturesok =  fu.readLine(path, images);
                     if (texturesok)
                         obj->addTexture(images,"InitGL::add3DObject");
                     else
                         logwarn("Engine::loadTexturedCube: Konnte Textures nicht laden ! ","CEngine::loadTexturedCube");
                 }
                 else {

                     int count = 0;

                     if (s3D.texture0 != "" ) {
                         images.push_back(PATH::ROOT_DIR + s3D.texture0);
                         count ++;
                     }

                     if (s3D.texture1 != "" ) {
                         images.push_back(PATH::ROOT_DIR + s3D.texture1);
                         count ++;
                     }

                     if (s3D.texture2 != "" ) {
                         images.push_back(PATH::ROOT_DIR + s3D.texture2);
                         count ++;
                     }

                     if (s3D.texture3 != "" ) {
                         images.push_back(s3D.texture3);
                         count ++;
                     }

                     if (s3D.texture4 != "" ) {
                         images.push_back(PATH::ROOT_DIR + s3D.texture4);
                         count ++;
                     }

                     if (count > 0) {
                        obj->addTexture(images,"InitGL::add3DObject");
                        loginfo("added " + IntToString(count) + " Textures ", "Engine::loadTexturedCubes");
                     }
                     else
                         obj->SetHasTextures(false);                 }

                 loginfo("s3D initialisisert ","CEngine::init3D");
                 add2List(obj,LIGHT_SHADER); //LIGHT_SHADER)

             }
             else
                 logwarn("konnte s3D nicht initialisieren !!", "CEngine::init3D" );

             loginfo("Prepare for next Object: ","CEngine::init3D");
             logEmptyLine();
        }
    }

    for (int i=0; i< 1; i++)
        setupTemplate(i);
    return true;
}

void CEngine::setupTemplate(int i) {

    CCube * obj = new CCube();
    glm::vec3 translate = glm::vec3(1+ static_cast<float>(i), 1 +static_cast<float>(i),0 ) ;
    glm::vec3 rotate = glm::vec3(1.0,1.0,1.0);
    glm::vec3 scale = glm::vec3(1.0,1.0,1.0);
    glm::vec4 color = glm::vec4(0,0,1,1);

    std::string tex0 = PATH::ROOT_DIR + "images/bluefish.png";
    std::string tex1 = PATH::ROOT_DIR + "images/wall.png";


    obj->SetHasTextures( true);

    obj->SetColor(color);
    obj->SetFirstTranslate( ((i % 2) == 0 ? true:false));
    obj->Rotate(rotate );
    obj->Translate(translate);
    obj->Scale(scale);
    obj->SetHasAlpha(true);
    obj->SetFrontFace(GL_CCW);

    //----------------------------------------
    // Add textures , if we have some
    // ---------------------------------------

    std::vector<std::string> images;
    images.push_back(tex0);
    images.push_back(tex1);
    obj->addTexture(images,"InitGL::add3DObject");
    add2List(obj,LIGHT_SHADER); //LIGHT_SHADER)
}

bool CEngine::loadCockpits() {
    loginfo("Lade Datei |Cockpits.cfg | ","CEngine::loadCockpits");

     // Liste mit Cockpits abarbeiten :

    if (objectCockpitList.empty() )
        return false;

    for (unsigned int i = 0; i < objectCockpitList.size(); i++) {

         std::string path = COCKPIT_CFG + objectCockpitList[i];

         loginfo("Erstelle Object: .......< " + path+ " >","Engine::loadCockpits");

         fileUtil * objreader = new fileUtil;
         std::vector<std::string> objconfig;
         objreader->readLine(path, objconfig);


         if( ! objconfig.empty() ) {

             s3DStruct s3D;

             if (init3DStruct(s3D,objconfig)) {

                 CCube * obj = new CCube();
                 //obj->SetColor(glm::vec4(s3D.color.x, s3D.color.y, s3D.color.z, s3D.color.w));
                 if ( s3D.textures == "" )
                     obj->SetHasTextures( false);
                 else
                     obj->SetHasTextures( true);

                 obj->SetColor(glm::vec4(s3D.color.x, s3D.color.y, s3D.color.z, s3D.color.w));
                 obj->SetFirstTranslate( ( s3D.firstTranslate == 1) ? true: false);
                 obj->Rotate(glm::vec3(s3D.trans.rotate.x, s3D.trans.rotate.y, s3D.trans.rotate.z) );
                 obj->Translate(glm::vec3(s3D.trans.translate.x, s3D.trans.translate.y, s3D.trans.translate.z));
                 obj->Scale(glm::vec3(s3D.trans.scale.x, s3D.trans.scale.y, s3D.trans.scale.z));
                 obj->SetHasAlpha(true);
                 obj->SetFrontFace(GL_CW);

                 //----------------------------------------
                 // Add textures , if we have some
                 // ---------------------------------------
                 bool texturesok;
                 std::vector<std::string> images;

                 std::string path = s3D.textures;
                 if ( s3D.textures != "" || s3D.textures != "NONE" ) {

                     path = PATH::ROOT_DIR + path;
                     fileUtil fu;

                     texturesok =  fu.readLine(path, images);
                     if (texturesok)
                         obj->addTexture(images,"InitGL::addCockpitTexture");
                     else
                         logwarn("Engine::loadCockpits: Konnte Textures nicht laden ! ","CEngine::loadCockpits");
                 }
                 loginfo("Cockpit initialisisert ","CEngine::loadCockpit");

                 obj->initShader(COLOR_SHADER,cubeshaderprog_color);
                 obj->initShader(TEXTURE_SHADER,cubeshaderprog_tex);
                 obj->initShader(LIGHT_SHADER, cubeshaderprog_normals);
                 obj->initShader(LIGHT_COLOR_SHADER, cubeshaderprog_color_normal);
                 obj->initShader(GLASS_SHADER,glasshader);
                 obj->setActiveShader(TEXTURE_SHADER);
                 obj->SetFrontFace(GL_CW);

                 cockpit->setMesh(obj);
             }
             else
                 logwarn("konnte Cockpit nicht initialisieren !!", "CEngine::loadCockpits" );
                // Hier die neuen stringpart functions einbauen

             loginfo("Prepare for next cockpit: ","CEngine::loadcockpit");
             logEmptyLine();
        }
    }
    return true;
}


bool CEngine::loadSpheres(){
    loginfo("Lade Datei | TexturedSpheres.cfg|","CEngine::loadTexturedSpheres");

    // Liste mit Objekten abarbeiten :
    if (objectTexturedSpheresList.empty() )
        return false;

    for (unsigned int i = 0; i < objectTexturedSpheresList.size(); i++) {

         std::string path = SPHERE_CFG + objectTexturedSpheresList[i];

         loginfo("Erstelle Textured Spheres: .......< " + path+ " >","Engine::LoadTexturedSpheres");

         fileUtil * objreader = new fileUtil;
         std::vector<std::string> objconfig;
         objreader->readLine(path, objconfig);


         if( ! objconfig.empty() ) {

             sSphereStruct sphere;

             if (initSphereStruct(sphere,objconfig)) {

                 CSphere * obj = new CSphere();
                 //obj->SetColor(glm::vec4(s3D.color.x, s3D.color.y, s3D.color.z, s3D.color.w));
                 bool texturesok;
                 std::vector<std::string> images;

                 std::string path = sphere.textures;
                 if ( sphere.textures != "NONE" ) {

                     path = PATH::ROOT_DIR + path;
                     fileUtil fu;

                     texturesok =  fu.readLine(path, images);
                     if (texturesok)
                         obj->addTexture(images,"InitGL::add3DObject");
                     else
                         logwarn("Engine::loadTexturedCube: Konnte Textures nicht laden ! ","CEngine::loadTexturedCube");
                 }
                 else {

                     int count = 0;

                     if (sphere.texture0 != "" ) {
                         images.push_back(PATH::ROOT_DIR + sphere.texture0);
                         count ++;
                     }

                     if (sphere.texture1 != "" ) {
                         images.push_back(PATH::ROOT_DIR + sphere.texture1);
                         count ++;
                     }

                     if (sphere.texture2 != "" ) {
                         images.push_back(PATH::ROOT_DIR + sphere.texture2);
                         count ++;
                     }

                     if (sphere.texture3 != "" ) {
                         images.push_back(PATH::ROOT_DIR + sphere.texture3);
                         count ++;
                     }

                     if (sphere.texture4 != "" ) {
                         images.push_back(PATH::ROOT_DIR + sphere.texture4);
                         count ++;
                     }

                     if (count > 0) {
                        obj->addTexture(images,"InitGL::add3DObject");
                        loginfo("added " + IntToString(count) + " Textures ", "Engine::loadTexturedSphere");
                     }
                     else
                         obj->SetHasTextures(false);
                  }

                 obj->SetColor(glm::vec4(sphere.color.x, sphere.color.y, sphere.color.z, sphere.color.w));
                 obj->SetFirstTranslate( ( sphere.firstTranslate == 1) ? true: false);
                 obj->Rotate(glm::vec3(sphere.trans.rotate.x, sphere.trans.rotate.y, sphere.trans.rotate.z) );
                 obj->Translate(glm::vec3(sphere.trans.translate.x, sphere.trans.translate.y, sphere.trans.translate.z));
                 obj->Scale(glm::vec3(sphere.trans.scale.x, sphere.trans.scale.y, sphere.trans.scale.z));
                 obj->setRadius(sphere.radius);
                 obj->setCountMeshPoints(sphere.meshpoints);

                 obj->setUp();
                 obj->SetFrontFace(GL_CCW);
                 loginfo("Sphere initialisisert ","CEngine::initSphere");

                 add2List(obj,LIGHT_COLOR_SHADER);
             }
             else
                 logwarn("konnte Sphere nicht initialisieren !!", "CEngine::iniSpheres" );
                // Hier die neuen stringpart functions einbauen

             loginfo("Prepare for next Object: ","CEngine::initSpheres");
             logEmptyLine();
        }
    }
    return true;
}

void CEngine::InitButtons() {

    logEmptyLine();
    loginfo("============================");
    loginfo("Erstelle Buttons ...........");
    loginfo("============================");

    loadButtons();
}

void CEngine::loadButtons() {
    // Open file
    bool ok;
    fu = new fileUtil();

    ok = fu->readLine(BUTTONS_CFG + "ButtonList.cfg", btnList);

    if (ok) {
        loginfo("Lade Datei |ButtonList.cfg|","CEngine::loadbuttons");
        logEmptyLine();

        for (unsigned int i = 0; i < btnList.size(); i++  ){

            std::string path = BUTTONS_CFG + btnList[i];

            fileUtil * btnreader = new fileUtil;
            std::vector<std::string> btnconfig;
            btnreader->readLine(path, btnconfig);



            if ( ! btnconfig.empty() ) {

                loginfo("Erstelle Button: .......< " + path+ " >", "Engine::loadButtons");

                sButtonStruct btnStruct;
                if  (initButtonStruct(btnStruct,btnconfig) ) {
                    sPoint pos;
                    CButton * btn = new CTextButton(_ResX,_ResY ,btnStruct.path,"",pos,getShaderPtr());//   btnStruct.path);
                    btn->setPos(btnStruct.PosX,btnStruct.PosY);
                    btn->setSize(btnStruct.SizeX, btnStruct.SizeY);
                    btn->setbuttonColors(glm::vec3(btnStruct.ImageRed,btnStruct.ImageGreen,btnStruct.ImageBlue),
                                         glm::vec3(btnStruct.TextRed,btnStruct.TextGreen,btnStruct.TextBlue));

                    switch (i) {
                        case 0: btn ->AddHandler(funcToogleSkybox); break;
                        case 1: btn ->AddHandler(EngineTestFunc2); break;
                        case 2: btn ->AddHandler(EngineTestFunc3); break;
                    default:
                        btn ->AddHandler(EngineTestFunc4);
                    }
                    if (btnStruct.Enable > 0 )
                        btn->enable();
                    else
                        btn->disable();
                    btn->setText("Edit");
                    addButton(btn);

                    loginfo(".........Done", "Engine::loadButtons");
                    logEmptyLine();
                }
            }
        }
    }
    else
        logwarn("Fehler: Datei | config/ButtonList nicht gefunden ! |");

    logEmptyLine() ;
    loginfo("----------------------------");
    loginfo(" Load Button Objects ");
    loginfo("        READY");
    loginfo("----------------------------");

}

std::string &CEngine::getValueItem(std::string &s, std::string erasestring) {
    return s.erase(0,erasestring.length() ) ;
}

bool CEngine::initLandscape(sLandscape &ls, std::vector<std::string> &cfg){
    if (cfg.size() >= CFG_3D_SIZE ) {

        //+---------------------------------------------------------------------+
        //+     VORGEHEN :                                                      |
        //+     Liste abarbeiten, Teilstring bis " " ermitteln,                 |
        //+     Variablen name = Teilstring --> 2. Teilstring in Wert wandeln   |
        //+     und in der s3DStruct zuweisen                                   |
        //+---------------------------------------------------------------------+

        for (uint i = 0; i < cfg.size(); i++) {
            std::vector<std::string> parts = split(cfg.at(i), SPACE);

            if (parts.at(0) == "colorRed")
                ls.color.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "colorGreen")
                ls.color.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "colorBlue")
                ls.color.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "colorAlpha")
                ls.color.w = StringToFloat(parts.at(1));

            if (parts.at(0) == "hasLight")
                ls.hasLight = StringToInt(parts.at(1));

            if (parts.at(0) == "textures")
                ls.textures = parts.at(1);

            if (parts.at(0) == "translateX")
                ls.trans.translate.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "translateY")
                ls.trans.translate.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "translateZ")
                ls.trans.translate.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "rotateX")
                ls.trans.rotate.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "rotateY")
                ls.trans.rotate.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "rotateZ")
                ls.trans.rotate.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "scaleX")
                ls.trans.scale.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "scaleY")
                ls.trans.scale.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "scaleZ")
                ls.trans.scale.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "patchX")
                ls.patchX = StringToInt(parts.at(1));

            if (parts.at(0) == "patchZ")
                ls.patchZ = StringToInt(parts.at(1));

            if (parts.at(0) == "rasterX")
                ls.rasterX = StringToFloat(parts.at(1));

            if (parts.at(0) == "rasterZ")
                ls.rasterZ = StringToFloat(parts.at(1));

            if (parts.at(0) == "texture0")
                ls.texture0 = parts.at(1);

            if (parts.at(0) == "texture1")
                ls.texture1 = parts.at(1);

            if (parts.at(0) == "texture2")
                ls.texture2 = parts.at(1);

            if (parts.at(0) == "texture3")
                ls.texture3 = parts.at(1);

            if (parts.at(0) == "texture4")
                ls.texture4 = parts.at(1);

        }
        return true;

    }
    return false;
}

bool CEngine::init3DStruct(s3DStruct &d3s, std::vector<std::string> &cfg){
    if (cfg.size() >= CFG_3D_SIZE ) {

        //+---------------------------------------------------------------------+
        //+     VORGEHEN :                                                      |
        //+     Liste abarbeiten, Teilstring bis " " ermitteln,                 |
        //+     Variablen name = Teilstring --> 2. Teilstring in Wert wandeln   |
        //+     und in der s3DStruct zuweisen                                   |
        //+---------------------------------------------------------------------+

        for (uint i = 0; i < cfg.size(); i++) {
            std::vector<std::string> parts = split(cfg.at(i), SPACE);

            if (parts.at(0) == "originX")
                d3s.origin.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "originY")
                d3s.origin.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "originZ")
                d3s.origin.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "colorRed")
                d3s.color.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "colorGreen")
                d3s.color.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "colorBlue")
                d3s.color.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "colorAlpha")
                d3s.color.w = StringToFloat(parts.at(1));

            if (parts.at(0) == "hasLight")
                d3s.hasLight = StringToInt(parts.at(1));

            if (parts.at(0) == "textures")
                d3s.textures = parts.at(1);

            if (parts.at(0) == "translateX")
                d3s.trans.translate.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "translateY")
                d3s.trans.translate.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "translateZ")
                d3s.trans.translate.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "rotateX")
                d3s.trans.rotate.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "rotateY")
                d3s.trans.rotate.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "rotateZ")
                d3s.trans.rotate.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "scaleX")
                d3s.trans.scale.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "scaleY")
                d3s.trans.scale.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "scaleZ")
                d3s.trans.scale.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "firstTranslate")
                d3s.firstTranslate = StringToInt(parts.at(1));

            if (parts.at(0) == "texture0")
                d3s.texture0 = parts.at(1);

            if (parts.at(0) == "texture1")
                d3s.texture1 = parts.at(1);

            if (parts.at(0) == "texture2")
                d3s.texture2 = parts.at(1);

            if (parts.at(0) == "texture3")
                d3s.texture3 = parts.at(1);

            if (parts.at(0) == "texture4")
                d3s.texture4 = parts.at(1);

        }
        return true;

    }
    return false;
}

bool CEngine::initSphereStruct(sSphereStruct &sSphere, std::vector<std::string> &cfg){
    if (cfg.size() <= CFG_SPHERE_SIZE ) {

        //+---------------------------------------------------------------------+
        //+     VORGEHEN :                                                      |
        //+     Liste abarbeiten, Teilstring bis " " ermitteln,                 |
        //+     Variablen name = Teilstring --> 2. Teilstring in Wert wandeln   |
        //+     und in der s3DStruct zuweisen                                   |
        //+---------------------------------------------------------------------+

        for (uint i = 0; i < cfg.size(); i++) {
            std::vector<std::string> parts = split(cfg.at(i), SPACE);

            if (parts.at(0) == "originX")
                sSphere.origin.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "originY")
                sSphere.origin.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "originZ")
                sSphere.origin.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "colorRed")
                sSphere.color.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "colorGreen")
                sSphere.color.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "colorBlue")
                sSphere.color.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "colorAlpha")
                sSphere.color.w = StringToFloat(parts.at(1));

            if (parts.at(0) == "hasLight")
                sSphere.hasLight = StringToInt(parts.at(1));

            if (parts.at(0) == "textures")
                sSphere.textures = parts.at(1);

            if (parts.at(0) == "translateX")
                sSphere.trans.translate.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "translateY")
                sSphere.trans.translate.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "translateZ")
                sSphere.trans.translate.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "rotateX")
                sSphere.trans.rotate.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "rotateY")
                sSphere.trans.rotate.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "rotateZ")
                sSphere.trans.rotate.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "scaleX")
                sSphere.trans.scale.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "scaleY")
                sSphere.trans.scale.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "scaleZ")
                sSphere.trans.scale.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "firstTranslate")
                sSphere.firstTranslate = StringToInt(parts.at(1));

            if (parts.at(0) == "texture0")
                sSphere.texture0 = parts.at(1);

            if (parts.at(0) == "texture1")
                sSphere.texture1 = parts.at(1);

            if (parts.at(0) == "texture2")
                sSphere.texture2 = parts.at(1);

            if (parts.at(0) == "texture3")
                sSphere.texture3 = parts.at(1);

            if (parts.at(0) == "texture4")
                sSphere.texture4 = parts.at(1);

            if (parts.at(0) == "radius")
                sSphere.radius = StringToFloat(parts.at(1));

            if (parts.at(0) == "meshpoints")
                sSphere.meshpoints = StringToFloat(parts.at(1));
        }
        return true;

    }
    return false;
}


bool CEngine::initButtonStruct(sButtonStruct &bs, std::vector<std::string> cfg) {

    if (cfg.size() >= CFG_BUTTON_SIZE ) {
        bs.path = getValueItem(cfg[0],"Image: ");
        loginfo("Image Path: "+ bs.path);

        bs.PosX = StringToFloat(getValueItem(cfg[1],"PositionX: "));

        bs.PosY = StringToFloat(getValueItem(cfg[2],"PositionY: "));

        bs.SizeX =  StringToFloat(getValueItem(cfg[3],"SizeX: "));

        bs.SizeY =  StringToFloat(getValueItem(cfg[4],"SizeY: "));

        bs.Enable = StringToInt(getValueItem(cfg[5],"Enable: "));

        bs.ImageRed = StringToFloat(getValueItem(cfg[6],"BGRed: "));

        bs.ImageGreen = StringToFloat(getValueItem(cfg[7],"BGGreen: "));

        bs.ImageBlue = StringToFloat(getValueItem(cfg[8],"BGBlue: "));

        bs.TextRed = StringToFloat(getValueItem(cfg[9],"TextColorRed: "));

        bs.TextGreen = StringToFloat(getValueItem(cfg[10],"TextColorGreen: "));

        bs.TextBlue = StringToFloat(getValueItem(cfg[11],"TextColorBlue: "));

        return true;
    }
    else
        return false;
}




