#if FRONTEND_LED_MATRIX
#include "led-matrix/led-matrix-frontend.h"
#include "serial-logger.h"
#include "led-matrix/led-matrix-web-config.h"

LedMatrixFrontend::LedMatrixFrontend() {
  this->ledMatrixWebConfig = new LedMatrixWebConfig();
  this->logger = new SerialLogger();
  this->ledmatrix = new PxMATRIX(MATRIX_WIDTH,MATRIX_HEIGHT,P_LAT, P_OE,P_A,P_B,P_C);
  this->display_ticker = new Ticker;
}

CustomWebConfig* LedMatrixFrontend::getCustomWebConfig() {
  return ledMatrixWebConfig;
}

Logger* LedMatrixFrontend::getLogger() {
  return logger;
}

void LedMatrixFrontend::init() {
  this->ledmatrix->begin(ROW_PATERN);                 // Row patern
  //this->ledmatrix->setBrightness(this->ledMatrixWebConfig->getBrightness());       // Brightness: 0-255, set in config
  //this->ledmatrix->setBrightness(10);
  
     // Some standard colors
    // uint16_t myRED = ledmatrix.color565(255, 0, 0);
    // uint16_t myGREEN = ledmatrix.color565(0, 255, 0);
    // uint16_t myBLUE = ledmatrix.color565(0, 0, 255);
    // uint16_t myWHITE = ledmatrix.color565(255, 255, 255);
    // uint16_t myYELLOW = ledmatrix.color565(255, 255, 0);
    // uint16_t myCYAN = ledmatrix.color565(0, 255, 255);
    // uint16_t myMAGENTA = ledmatrix.color565(255, 0, 255);
    // uint16_t myBLACK = ledmatrix.color565(0, 0, 0);
    // uint16_t myCOLORS[8]={myRED,myGREEN,myBLUE,myWHITE,myYELLOW,myCYAN,myMAGENTA,myBLACK};
}

void LedMatrixFrontend::connected(Config config, DataSource *dataSource) {
  this->ledmatrix->setBrightness(this->ledMatrixWebConfig->getBrightness());       // Brightness: 0-255, set in config
}

void LedMatrixFrontend::doLoop() {
  this->ledmatrix->display(50);
}

void LedMatrixFrontend::updateDisplayModel(DisplayModel *displayModel) {
  this->ledmatrix->clearDisplay();
  this->ledmatrix->setTextSize(1);
  this->ledmatrix->setTextColor(this->ledmatrix->color565(0, 255, 0));
  this->ledmatrix->setCursor(0,0);
  this->ledmatrix->print(displayModel->pm25);
  this->ledmatrix->setCursor(34,0);
  this->ledmatrix->print(displayModel->pm25rel);
  this->ledmatrix->print("%");
  this->ledmatrix->setCursor(0,8);
  this->ledmatrix->print(displayModel->pm10);
  this->ledmatrix->setCursor(34,8);
  this->ledmatrix->print(displayModel->pm10rel);
  this->ledmatrix->print("%");

}

void LedMatrixFrontend::updateDataSourceStatus(DataSourceStatus status) {

}

#endif