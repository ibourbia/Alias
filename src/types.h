#include <map>
#include <vector>
#ifndef TYPES_H
#define TYPES_H

enum Type {
	 RS ,
	 IB ,
	 CH,
	 FS,
	 LTS
};
static std::map<Type,bool> allTypesValues = { {RS, true}, {IB, true}, {CH, true}, {FS, false}, {LTS, false} };
static std::vector<Type> keys = { RS, IB, CH, FS, LTS };

static std::string display(Type indice)
{
    switch(indice){
    case 0:
        return "RS";
        break;
    case 1:
        return "IB";
        break;
    case 2:
        return "CH";
        break;
    case 3 :
        return "FS";
        break;
    case 4 :
        return "LTS";
        break;
    default:
        throw std::invalid_argument("wrong indice");
    }
}
static int displayInhib(Type indice)
{
    switch(indice){
    case 0:
        return 0;
        break;
    case 1:
        return 0;
        break;
    case 2:
        return 0;
        break;
    case 3 :
        return 1;
        break;
    case 4 :
        return 1;
        break;
    default:
        throw std::invalid_argument("wrong indice");
    }
}
#endif
