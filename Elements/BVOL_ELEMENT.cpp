#include "PROVIDER.h"
#include "BVOL_ELEMENT.h"

Bvol_Element::Bvol_Element()
{

}
Bvol_Element::Bvol_Element(ARG1 arg) : Element(arg)
{
   
}

ObjectProvider<Element, Bvol_Element, 1> BVOLProvider("BVOL");