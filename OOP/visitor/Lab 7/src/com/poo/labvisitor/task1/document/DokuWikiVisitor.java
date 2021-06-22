package com.poo.labvisitor.task1.document;

import java.util.ArrayList;

public class DokuWikiVisitor implements DocumentVisitor {
        StringBuilder built  = new StringBuilder();
        ArrayList<TextSegment> textSegments = new ArrayList<>();

    public DokuWikiVisitor(ArrayList<TextSegment> textSegments) {
        this.textSegments = textSegments;
    }

    @Override
    public void visit(ItalicTextSegment italicTextSegment) {
        built.append("//");
        built.append(italicTextSegment.getContent());
        built.append("//");
    }

    @Override
    public void visit(BoldTextSegment boldTextSegment) {
        built.append("**");
        built.append(boldTextSegment.getContent());
        built.append("**");
    }

    @Override
    public void visit(PlainTextSegment plainTextSegment) {
        built.append(plainTextSegment.getContent());
    }

    @Override
    public void visit(UrlSegment urlSegment) {
        StringBuilder url2 = new StringBuilder();
        built.append("[[");
        built.append(urlSegment.getContent());
        url2.append(urlSegment.name);
        built.append("|");
        url2.append("]]");
        built.append(url2);
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
