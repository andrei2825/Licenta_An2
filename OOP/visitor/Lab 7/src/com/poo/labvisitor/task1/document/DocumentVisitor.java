package com.poo.labvisitor.task1.document;

public interface DocumentVisitor {
    public void visit(ItalicTextSegment italicTextSegment);

    public void visit(BoldTextSegment boldTextSegment);

    public void visit(PlainTextSegment plainTextSegment);

    public void visit(UrlSegment urlSegment);

    public StringBuilder getDocumment();

}
