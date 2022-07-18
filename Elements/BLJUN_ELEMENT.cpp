#include "PROVIDER.h"
#include "BLJUN_ELEMENT.h"

Bljun_Element::Bljun_Element()
{

}
Bljun_Element::Bljun_Element(ARG1 arg) : Element(arg)
{
   
}

ObjectProvider<Element, Bljun_Element, 1> BLJUNProvider("BLJUN");