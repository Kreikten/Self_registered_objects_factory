#include "PROVIDER.h"
#include "CFD_ELEMENT.h"

Cfd_Element::Cfd_Element()
{

}
Cfd_Element::Cfd_Element(ARG1 arg) : Element(arg)
{
   
}

ObjectProvider<Element, Cfd_Element, 1> CFDProvider("CFD");