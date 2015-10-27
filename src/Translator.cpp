#include <iostream>
#include "Translator.h"
#include "Codegen.h"


Translator::Translator() {
    lChild = NULL;
    rChild = NULL;
    parent = NULL;
}

void Translator::setLeft(const Translator *l) {
    lChild = l;
}

void Translator::setRight(const Translator *r) {
    rChild = r;
}

void Translator::setParent(const Translator *p) {
    parent = p;
}





ScanTranslator::ScanTranslator(const Schema *s) : tp(s->getTupPtr()) {};

void ScanTranslator::produce() const {
    assert(lChild == NULL);
    assert(rChild == NULL);
    assert(parent != NULL);

    consume();
}

void ScanTranslator::consume() const {
    codegen::scanConsume(tp, parent);
}



PrintTranslator::PrintTranslator(const Schema *s) {
    types = (int *)&(s->getTypes()->front());
};

void PrintTranslator::produce() const {
    assert(lChild != NULL);
    assert(rChild == NULL);
    assert(parent == NULL);

    lChild->produce();
}

void PrintTranslator::consume() const {
    codegen::printConsume(types);
}