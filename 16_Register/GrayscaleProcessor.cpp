/**
 * ============================================================================
 * File: GrayscaleProcessor.cpp
 * 
 * --- DESIGN OVERVIEW:
 * Concrete implementation of the Processor interface. This component 
 * automatically registers itself into the Registry upon initialization.
 * ============================================================================
 */

#include "Register.h"

class GrayscaleProcessor : public Processor
{
public:
   Image process(const Image& image) const override
   {
      return image + " grayscaled";
   }

   std::string getName() const override 
   { 
      return "Grayscale"; 
   }
};

// Auto-register using the helper
static Register<GrayscaleProcessor> reg("Grayscale");

//================================================================================ END
