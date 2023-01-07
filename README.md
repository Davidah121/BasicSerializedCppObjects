# BasicSerializedCppObjects
A simple solution to Serialization for C++ structures and objects.</br></br>
It should be portable provided the compiler supports 'typeid' and the preprocessor '#' for strings and '##' for concatenation</br>

# Usage
For any class that should be Serialized, it should inherit from SerializedObject.</br>
This allows it to store a list of SerializedData and be saved and loaded.</br></br>

For any data that should be Serialized, use the preprocessor SERIALIZE or its variant</br>
to create a new SerializedData object. These get stored in the parents list of SerializedData variables for later use.</br></br>

For special cases, say if the data being serialized is not apart of a class, use SERIALIZE_NOCLASS</br>
If the typename should be adjusted, say to use a preferred name, SERIALIZE_TYPENAME and SERIALIZE_TYPENAME_NOCLASS exist</br></br>

Typenames are not strictly portable nor do they pick the "pretty name".</br>
&emsp;&emsp;Ex: class std::string -> class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> ></br></br>
To help with this, there is a set of functions for setting the preferred name for types. Some defaults are available but none are there by default.</br>
SerializedObject::addPrettyName() and SerializedObject::getAlternateName() exist for these purposes.</br></br>

As for loading and saving data, by default only primitives and std::string are supported.</br>
To support more types, external load and save functions can be set to deal with them.</br></br>

# Additional Notes
Even though a SerializedObject inherits from SerializedData, it will not save the type or name. It must be serialized separately.</br>
&emsp;&emsp;Using SERIALIZE or SERIALIZE_NOCLASS will set its type and name when saved.</br></br>

All data is saved as an XML file so a basic class for handling XML files is provided. Ideally, it would be replaced with more robust code.</br></br>

The save and loading function could be reworked to save std::vector, std::array, and the like but since they are templates, it gets a bit complex.</br></br>

This is separated from the main library where the SimpleXml, SimpleFile, and StringTools code originates from for portability.</br></br>

Some test classes are included to show implementation along with the source.cpp file. They can be ignored.</br></br>
