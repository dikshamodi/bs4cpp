class PageElement { 
    htmlcxx::HTML::Node nodeElement;   
    tree<htmlcxx::HTML::Node>::iterator myIterator;
    tree<htmlcxx::HTML::Node>* myDom;

    public:    
        std::map<std::string, std::string> attrs;  
        
        PageElement(htmlcxx::HTML::Node & node, auto myIterator, auto myDom) {
            this -> nodeElement = node;
            this -> myIterator = myIterator;
            this -> myDom = myDom;
            nodeElement.parseAttributes();
            attrs = (nodeElement).attributes();
        }
        
        std::string name() {
            return (std::string)(nodeElement);
        }
        
        PageElement parent() {
            auto parent_iterator = myDom->parent(myIterator);
            if (parent_iterator == NULL) 
                parent_iterator = myIterator;
            return PageElement(*parent_iterator, parent_iterator, myDom);
        }

        PageElement next_element() {
            auto iteratorCurrentNode = myIterator;
            std::string textCurrentNode  = "";      
            auto endIterator = myDom -> end();

            while (textCurrentNode == "" && ++iteratorCurrentNode != endIterator) {
               textCurrentNode = trimWhitespace(iteratorCurrentNode -> text());
            }        
            if(iteratorCurrentNode == endIterator) {
                iteratorCurrentNode = myIterator;
            }   
            return PageElement(*iteratorCurrentNode, iteratorCurrentNode, myDom);
        }

        PageElement previous_sibling() {
            auto prevSiblIterator = myDom -> previous_sibling(myIterator);
            if (prevSiblIterator == NULL) {
                prevSiblIterator = myIterator;
            }
            return PageElement(*prevSiblIterator, prevSiblIterator, myDom);
        }
        
};

std::ostream& operator<<(std::ostream& out, PageElement element) {
    std::string name = element.name();
    out << name;
    return out;
}
