
#include <iostream>
#include <leptonica/allheaders.h>
#include <tesseract/baseapi.h>

#include "ocrtask.h"

using namespace clippy;

OcrTask::OcrTask() {}
OcrTask::~OcrTask() {}

void OcrTask::run(std::filesystem::path path) {

  path = "page-0.png";

  auto ocr =
      std::unique_ptr<tesseract::TessBaseAPI>{new tesseract::TessBaseAPI{}};

  if (ocr->Init(nullptr, "eng")) {
    std::cerr << "Failed to initialize tesseract\n";
    return;
  }

  auto image = pixRead(path.string().c_str());
  if (!image) {
    std::cerr << "Failed to read image\n";
    return;
  }

  ocr->SetImage(image);

  auto outText = std::unique_ptr<char[]>{ocr->GetUTF8Text()};
  std::cout << "OCR output: " << outText << "\n";

  pixDestroy(&image);
  ocr->End();
}