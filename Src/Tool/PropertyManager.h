#ifndef SRC_TOOL_PROPERTYMANAGER_H_

#define SRC_TOOL_PROPERTYMANAGER_H_

#include <exception>
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>

namespace CC {

// Created by : eXpl0it3r : https://github.com/SFML/SFML/wiki/Tutorial%3A-Object-Propertie
class IProperty {
 public:
    /// Class that represents the type for this class
    class Type_t {
     private:
        std::string mName;
     public:
        explicit Type_t(std::string theName) : mName(theName) {}
        std::string Name() const {
            return mName;
        }
    };

    /**
     * IProperty default constructor
     * @param[in] theType of property this property represents
     * @param[in] thePropertyID to use for this property
     */
    IProperty(std::string theType, const std::string thePropertyID);

    /**
     * IProperty destructor
     */
    virtual ~IProperty();

    /**
     * GetType will return the Type_t type for this property
     * @return the Type_t class for this property
     */
    Type_t* GetType(void);

    /**
     * GetID will return the Property ID used for this property.
     * @return the property ID for this property
     */
    const std::string GetID(void) const;

 protected:
    /**
     * SetType is responsible for setting the type of class this IProperty
     * class represents and is usually called by the IProperty derived class
     * to set theType.
     * @param[in] theType to set for this IProperty derived class
     */
    void SetType(std::string theType);

 private:
    // Variables
    ///////////////////////////////////////////////////////////////////////////
    /// The type that represents this class
    Type_t mType;
    /// The property ID assigned to this IProperty derived class
    const std::string mPropertyID;
};

/// The Template version of the IProperty class for custom property values
template<class TYPE = unsigned int>
class TProperty : public IProperty {
 public:
    /**
     * TProperty default constructor
     * @param[in] thePropertyID to use for this property
     */
    explicit TProperty(const std::string thePropertyID) :
        IProperty(typeid(TYPE).name(), thePropertyID) {
    }

    /**
     * GetValue will return the property value
     * @return the property value
     */
    TYPE& GetValue() {
        return mValue;
    }

    /**
     * GetValue will return the property value
     * @return the property value
     */
    const TYPE& GetValue() const {
        return mValue;
    }

 private:
    TYPE mValue;
};


class PropertyManager {
 public:
    /**
     * PropertyManager default constructor
     */
    PropertyManager();

    /**
     * PropertyManager deconstructor
     */
    virtual ~PropertyManager();

    /**
     * HasProperty returs true if thePropertyID specified exists in this
     * PropertyManager.
     * @param[in] thePropertyID to lookup in this PropertyManager
     * @return true if thePropertyID exists, false otherwise
     */
    bool HasID(const std::string thePropertyID);

    /**
     * GetProperty returns the property as type with the ID of thePropertyID.
     * @param[in] thePropertyID is the ID of the property to return.
     * @return the value stored in the found propery in the form of TYPE. If no
     * Property was found it returns the default value the type constructor.
     */
    template<class TYPE>
    const TYPE& Get(const std::string thePropertyID) const {
        auto it = mList.find(thePropertyID);
        if (it == mList.cend()) {
            std::cerr << "Trying to access property that doesn't exist in Get const method"
                      << std::endl;
            throw std::exception();
        } else {
            return static_cast<TProperty<TYPE>*>(it->second)->GetValue();
        }
    }

    /**
     * GetProperty returns the property as type with the ID of thePropertyID.
     * @param[in] thePropertyID is the ID of the property to return.
     * @return the value stored in the found propery in the form of TYPE. If no
     * Property was found it returns the default value the type constructor.
     */
    template<class TYPE>
    TYPE& Get(const std::string thePropertyID) {
        auto it = mList.find(thePropertyID);
        if (it == mList.cend()) {
            TProperty<TYPE>* anProperty =
                    new(std::nothrow) TProperty<TYPE>(thePropertyID);
            mList[anProperty->GetID()] = anProperty;
        }

        return static_cast<TProperty<TYPE>*>(
                    mList[thePropertyID])->GetValue();
    }

 private:
    // Variables
    ///////////////////////////////////////////////////////////////////////////
    /// A map of all Properties available for this PropertyManager class
    std::map<std::string, IProperty*> mList;
};  // PropertyManager class

}  // namespace CC

#endif  // SRC_TOOL_PROPERTYMANAGER_H_
