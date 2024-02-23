
#include <iostream>
#include <llama.h>

#include "llm.hpp"

using namespace clippy;

Llama::Llama() {}

Llama::~Llama() {}

void Llama::spit() {
  llama_backend_init();

  auto model_hparams = llama_model_default_params();
  auto model = llama_load_model_from_file("model.gguf", model_hparams);

  llama_free_model(model);

  llama_backend_free();
}
