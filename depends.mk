obj/URLList.o: src/URLList.cpp inc/URLList.h inc/URL.h \
 utils/inc/StringUtil.h
obj/PageQueue.o: src/PageQueue.cpp inc/PageQueue.h inc/Page.h inc/URL.h \
 utils/inc/StringUtil.h inc/WordIndex.h inc/BST.h inc/Pair.h \
 inc/OccurenceSet.h inc/Occurence.h inc/StopWords.h inc/URLList.h \
 inc/VisitedPages.h
obj/Pair.o: src/Pair.cpp inc/Pair.h inc/OccurenceSet.h inc/Occurence.h \
 inc/URL.h utils/inc/StringUtil.h inc/BST.h
obj/WordIndex.o: src/WordIndex.cpp inc/WordIndex.h inc/BST.h inc/Pair.h \
 inc/OccurenceSet.h inc/Occurence.h inc/URL.h utils/inc/StringUtil.h \
 inc/StopWords.h
obj/OccurenceSet.o: src/OccurenceSet.cpp inc/OccurenceSet.h \
 inc/Occurence.h inc/URL.h utils/inc/StringUtil.h inc/BST.h
obj/URL.o: src/URL.cpp inc/URL.h utils/inc/StringUtil.h \
 utils/inc/UnitTest.h
obj/Page.o: src/Page.cpp inc/URL.h utils/inc/StringUtil.h inc/WordIndex.h \
 inc/BST.h inc/Pair.h inc/OccurenceSet.h inc/Occurence.h inc/StopWords.h \
 inc/URLList.h inc/Page.h
obj/Visitedpages.o: src/Visitedpages.cpp inc/VisitedPages.h inc/Page.h \
 inc/URL.h utils/inc/StringUtil.h inc/WordIndex.h inc/BST.h inc/Pair.h \
 inc/OccurenceSet.h inc/Occurence.h inc/StopWords.h inc/URLList.h
obj/HTMLParser.o: src/HTMLParser.cpp inc/HTMLParser.h \
 utils/inc/URLInputStream.h utils/inc/InputStream.h \
 utils/inc/CS240Exception.h utils/inc/HTMLTokenizer.h \
 utils/inc/URLInputStream.h utils/inc/HTMLToken.h utils/inc/HTMLToken.h \
 inc/Page.h inc/URL.h utils/inc/StringUtil.h inc/WordIndex.h inc/BST.h \
 inc/Pair.h inc/OccurenceSet.h inc/Occurence.h inc/StopWords.h \
 inc/URLList.h
obj/XMLGen.o: src/XMLGen.cpp inc/XMLGen.h utils/inc/StringUtil.h \
 inc/VisitedPages.h inc/Page.h inc/URL.h inc/WordIndex.h inc/BST.h \
 inc/Pair.h inc/OccurenceSet.h inc/Occurence.h inc/StopWords.h \
 inc/URLList.h
obj/StopWord.o: src/StopWord.cpp inc/StopWords.h utils/inc/StringUtil.h
obj/Occurence.o: src/Occurence.cpp inc/Occurence.h inc/URL.h \
 utils/inc/StringUtil.h
