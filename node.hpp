#ifndef Node_hpp
#define Node_hpp


#include <iostream>
#include <memory>
#include <vector>
#include <cstdio>
#include <iostream>
#include <fstream>


enum type{
    Start,
    Html,
    Head,
    Title,
    TitleContent,
    Body,
    BodyContent,
    OList,
    ListElement,
    HeaderTags,
    WhiteSpace,
    TextContent,
    Text,
    SemanticTags,
    TextTags,
    TextTag,
    Anchor,
    AnchorLink,
    AnchorText,
    Image,
    ImageAttributes,
    Src,
    Alt,
    Header,
    Nav,
    Section,
    Article,
    Aside,
    Footer,
    H1,
    H2,
    H3,
    H4,
    H5,
    Paragraph,
    Strong,
    Em,
    Blockquote,
    Pre,
    A,
    Newline,
    Space, 
    UList
};  


class Node{
    private: 
        /// @brief Stores the value of the particular node.
        std::string* value ;
        /// @brief Stores the type of the Node of type symbols
        type nodeType;
        
    public:
        
        /// @brief Stores the children productions for a partiular node.
        std::vector< Node* > productions;

        /// @brief Used to access the private vaiable value.
        /// @return Returns the type of the Node.
        type getType(){
            return nodeType;
        }

        /// @brief Used to set the value of the private variable val
        /// @param val value to be store as the Node's value
        void setValue(std::string* val){
            value = val;
        }

        /// @brief Used as getter funtion for value variable
        /// @return Returns the Node's value
        std::string* getValue(){
            return value;
        }

        Node(type val) : nodeType(val) {
            value = new std::string("");
        }


};

#endif