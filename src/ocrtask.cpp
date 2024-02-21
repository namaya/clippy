
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

  // auto test = cv::Mat{};

  // cv::cvtColor(images[0], test, cv::COLOR_RGBA2BGR);
  // cv::imwrite("page-n0.png", images[0]);

  std::cout << "Done.\n";

  // auto ocr =
  //     std::unique_ptr<tesseract::TessBaseAPI>{new tesseract::TessBaseAPI{}};

  // if (ocr->Init(nullptr, "eng", tesseract::OEM_LSTM_ONLY)) {
  //   std::cerr << "Failed to initialize tesseract\n";
  //   return;
  // }

  // for (const auto &image : images) {
  //   auto pix = pixRead(image.string().c_str());
  //   if (!pix) {
  //     std::cerr << "Failed to read image\n";
  //     continue;
  //   }

  //   ocr->SetImage(pix);
  //   ocr->SetPageSegMode(tesseract::PSM_AUTO);

  //   auto outText = ocr->GetUTF8Text();

  //   std::cout << "OCR output: " << outText << "\n";

  //   pixDestroy(&pix);
  // }

  // ocr->SetImage(image);
  // ocr->SetPageSegMode(tesseract::PSM_AUTO);

  // // auto outText = ocr->GetUTF8Text();

  // // std::cout << "OCR output: " << outText << "\n";

  // // auto iter = ocr->GetIterator();

  // // do {
  // //   auto text = iter->GetUTF8Text(tesseract::RIL_BLOCK);
  // //   auto conf = iter->Confidence(tesseract::RIL_BLOCK);
  // //   int x1, y1, x2, y2;
  // //   iter->BoundingBox(tesseract::RIL_BLOCK, &x1, &y1, &x2, &y2);

  // //   std::cout << "text: " << text << " confidence: " << conf
  // //             << " BoundingBox: " << x1 << " " << y1 << " " << x2 << " "
  // <<
  // //             y2
  // //             << "\n";
  // // } while (iter->Next(tesseract::RIL_BLOCK));

  // ocr->Recognize(nullptr);

  // // auto boxes = std::unique_ptr<Boxa>{
  // //     ocr->GetComponentImages(tesseract::RIL_TEXTLINE, true, nullptr,
  // //     nullptr)};
  // auto boxes = std::unique_ptr<Boxa>{ocr->GetRegions(nullptr)};

  // std::cout << "Found " << boxes->n << " text blocks\n";

  // for (auto i = 0; i < boxes->n; i++) {
  //   auto box = boxaGetBox(boxes.get(), i, L_CLONE);

  //   ocr->SetRectangle(box->x, box->y, box->w, box->h);
  //   auto outText = std::unique_ptr<char[]>{ocr->GetUTF8Text()};
  //   auto confidence = ocr->MeanTextConf();

  //   std::cout << "Box " << i << ":\n";
  //   std::cout << "x: " << box->x << " y: " << box->y << " w: " << box->w
  //             << " h: " << box->h << "\n";
  //   std::cout << "confidence: " << confidence << "\n";
  //   std::cout << "OCR output: " << outText << "\n";
  // }

  // pixDestroy(&image);
  // ocr->End();
}