#include "PROVIDER.h"
#include "CH_ELEMENT.h"

Ch_Element::Ch_Element()
{

}
Ch_Element::Ch_Element(ARG1 arg) : Element(arg)
{
   
}

ObjectProvider<Element, Ch_Element, 1> CHProvider("CH");