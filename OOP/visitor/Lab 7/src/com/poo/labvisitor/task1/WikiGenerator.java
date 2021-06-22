package com.poo.labvisitor.task1;

import com.poo.labvisitor.task1.document.*;

import java.util.ArrayList;
import java.util.List;

/**
 * Uses visitors to parse documents and provide dokuwiki and markdown outputs.
 */
public class WikiGenerator {

    private final List<TextSegment> textSegments;

    public WikiGenerator(List<TextSegment> textSegments) {
        this.textSegments = textSegments;
    }

    public StringBuilder getDokuWikiDocument() {
        // TODO apply dokuwiki visitor on the text segments
        DocumentVisitor documentVisitor1 = new DokuWikiVisitor((ArrayList<TextSegment>) textSegments);
        return documentVisitor1.getDocumment();
    }

    public StringBuilder getMarkdownDocument() {
        // TODO apply Markdown visitor on the text segments
        DocumentVisitor documentVisitor2 = new MarkdownVisitor((ArrayList<TextSegment>) textSegments);
        return documentVisitor2.getDocumment();
    }


}
