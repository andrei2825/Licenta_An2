package com.poo.labvisitor.task1.document;

public class UrlSegment extends TextSegment{
    public String name;
    public UrlSegment(String content, String name) {
        super(content);
        this.name = name;
    }

    @Override
    public void accept(DocumentVisitor documentVisitor) {
        documentVisitor.visit(this);
    }
}
