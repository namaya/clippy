
#include <iostream>
#include <leptonica/allheaders.h>
#include <leptonica/pix_internal.h>
#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>

#include "ocrtask.h"

using namespace clippy;

OcrTask::OcrTask() {}
OcrTask::~OcrTask() {}

void OcrTask::recognize(std::vector<cv::Mat> images) {
  std::cout << "Recognizing " << images.size() << " images\n";

  auto ocr =
      std::unique_ptr<tesseract::TessBaseAPI>{new tesseract::TessBaseAPI{}};

  if (ocr->Init(nullptr, "eng", tesseract::OEM_LSTM_ONLY)) {
    std::cerr << "Failed to initialize tesseract\n";
    return;
  }

  for (const auto &image : images) {
    ocr->SetImage(image.data, image.cols, image.rows, image.channels(),
                  image.step);
    ocr->SetSourceResolution(120);
    ocr->SetPageSegMode(tesseract::PSM_AUTO);

    ocr->Recognize(0);

    auto boxes = std::unique_ptr<Boxa>{
        ocr->GetComponentImages(tesseract::RIL_BLOCK, true, nullptr, nullptr)};

    std::cout << "Found " << boxes->n << " text blocks\n";

    for (auto i = 0; i < boxes->n; i++) {
      auto box = boxaGetBox(boxes.get(), i, L_CLONE);

      ocr->SetRectangle(box->x, box->y, box->w, box->h);
      auto outText = std::unique_ptr<char[]>{ocr->GetUTF8Text()};
      auto confidence = ocr->MeanTextConf();

      std::cout << "Box " << i << ":\n";
      std::cout << "x: " << box->x << " y: " << box->y << " w: " << box->w
                << " h: " << box->h << "\n";
      std::cout << "confidence: " << confidence << "\n";
      std::cout << "OCR output: " << outText << "\n";

      boxDestroy(&box);
    }
  }

  ocr->End();
}