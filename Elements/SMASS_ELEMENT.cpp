#include "PROVIDER.h"
#include "SMASS_ELEMENT.h"

Smass_Element::Smass_Element()
{

}
Smass_Element::Smass_Element(ARG1 arg) : Element(arg)
{
   
}

ObjectProvider<Element, Smass_Element, 1> SMASSProvider("SMASS");