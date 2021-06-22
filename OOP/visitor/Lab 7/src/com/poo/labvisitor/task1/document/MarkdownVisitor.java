package com.poo.labvisitor.task1.document;

import java.util.ArrayList;

public class MarkdownVisitor implements DocumentVisitor {
        StringBuilder built  = new StringBuilder();
        ArrayList<TextSegment> textSegments = new ArrayList<>();

    public MarkdownVisitor(ArrayList<TextSegment> textSegments) {
        this.textSegments = textSegments;
    }

    @Override
    public void visit(ItalicTextSegment italicTextSegment) {
        built.append("_");
        built.append(italicTextSegment.getContent());
        built.append("_");
    }

    @Override
    public void visit(BoldTextSegment boldTextSegment) {
        built.append("__");
        built.append(boldTextSegment.getContent());
        built.append("__");
    }

    @Override
    public void visit(PlainTextSegment plainTextSegment) {
        built.append(plainTextSegment.getContent());
    }

    @Override
    public void visit(UrlSegment urlSegment) {
        StringBuilder url2 = new StringBuilder();
        built.append("[");
        built.append(urlSegment.getContent());
        built.append("](");
        built.append(urlSegment.name);
        built.append(")");
    }

    @Override
    public StringBuilder getDocumment() {
        StringBuilder returned = new StringBuilder();
        for (int i = 0; i < textSegments.size(); i++) {
            if (textSegments.get(i).getClass().toString().equals("class com.poo.labvisitor.task1.document.ItalicTextSegment")){
                visit((ItalicTextSegment) textSegments.get(i));
            }
            if (textSegments.get(i).getClass().toString().equals("class com.poo.labvisitor.task1.document.PlainTextSegment")){
                visit((PlainTextSegment) textSegments.get(i));
            }
            if (textSegments.get(i).getClass().toString().equals("class com.poo.labvisitor.task1.document.UrlSegment")){
                visit((UrlSegment) textSegments.get(i));
            }
            if (textSegments.get(i).getClass().toString().equals("class com.poo.labvisitor.task1.document.BoldTextSegment")){
                visit((BoldTextSegment) textSegments.get(i));
            }
        }
        returned = built;
        return returned;
    }
}
