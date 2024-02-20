
#include <iostream>
#include <leptonica/allheaders.h>
#include <leptonica/pix_internal.h>
#include <tesseract/baseapi.h>

#include "ocrtask.h"

using namespace clippy;

OcrTask::OcrTask() {}
OcrTask::~OcrTask() {}

void OcrTask::run(std::filesystem::path path) {

  // path = "page-1.png";
  path = "page-0.png";

  auto ocr =
      std::unique_ptr<tesseract::TessBaseAPI>{new tesseract::TessBaseAPI{}};

  if (ocr->Init(nullptr, "eng", tesseract::OEM_LSTM_ONLY)) {
    std::cerr << "Failed to initialize tesseract\n";
    return;
  }

  auto image = pixRead(path.string().c_str());
  if (!image) {
    std::cerr << "Failed to read image\n";
    return;
  }

  ocr->SetImage(image);
  ocr->SetPageSegMode(tesseract::PSM_AUTO);

  // auto outText = ocr->GetUTF8Text();

  // std::cout << "OCR output: " << outText << "\n";

  // auto iter = ocr->GetIterator();

  // do {
  //   auto text = iter->GetUTF8Text(tesseract::RIL_BLOCK);
  //   auto conf = iter->Confidence(tesseract::RIL_BLOCK);
  //   int x1, y1, x2, y2;
  //   iter->BoundingBox(tesseract::RIL_BLOCK, &x1, &y1, &x2, &y2);

  //   std::cout << "text: " << text << " confidence: " << conf
  //             << " BoundingBox: " << x1 << " " << y1 << " " << x2 << " " <<
  //             y2
  //             << "\n";
  // } while (iter->Next(tesseract::RIL_BLOCK));

  ocr->Recognize(nullptr);

  // auto boxes = std::unique_ptr<Boxa>{
  //     ocr->GetComponentImages(tesseract::RIL_TEXTLINE, true, nullptr,
  //     nullptr)};
  auto boxes = std::unique_ptr<Boxa>{ocr->GetRegions(nullptr)};

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
  }

  pixDestroy(&image);
  ocr->End();
}