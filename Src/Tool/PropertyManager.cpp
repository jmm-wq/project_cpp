#include "Tool/PropertyManager.h"

namespace CC {

IProperty::IProperty(std::string theType, const std::string thePropertyID) :
    mType(theType),
    mPropertyID(thePropertyID) {
}

IProperty::~IProperty() {
}

IProperty::Type_t* IProperty::GetType(void) {
    return &mType;
}

const std::string IProperty::GetID(void) const {
    return mPropertyID;
}

void IProperty::SetType(std::string theType) {
    mType = Type_t(theType);
}

PropertyManager::PropertyManager() {
}

PropertyManager::~PropertyManager() {
    // Make sure to remove all registered properties on desstruction
    std::map<const std::string, IProperty*>::iterator anProptertyIter;
    for (anProptertyIter = mList.begin();
        anProptertyIter != mList.end();
        ++anProptertyIter) {
        IProperty* anProperty = (anProptertyIter->second);
        delete anProperty;
        anProperty = nullptr;
    }
}

bool PropertyManager::HasID(const std::string thePropertyID) {
    bool anResult = false;

    // See if thePropertyID was found in our list of properties
    anResult = (mList.find(thePropertyID) != mList.end());

    // Return true if thePropertyID was found above, false otherwise
    return anResult;
}

}
