#pragma once

#include "Resource.h"
#include "ResourceFactoryBinary.h"

namespace SM64 {
class AudioBankFactoryV0 : public Ship::ResourceFactoryBinary {
  public:
    std::shared_ptr<Ship::IResource> ReadResource(std::shared_ptr<Ship::File> file,
                                                  std::shared_ptr<Ship::ResourceInitData> initData) override;
};
} // namespace SM64
