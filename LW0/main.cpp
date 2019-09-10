#include "arraysequence.cpp"
#include "arraysequence.hpp"
#include "listsequence.cpp"
#include "listsequence.hpp"
#define CATCH_CONFIG_MAIN
#include "/Users/levmarder/Documents/Прога/Catch/catch.hpp"

TEST_CASE("ArraySequence test 1") {
    ArraySequence<int>* seq = new ArraySequence<int>;
    REQUIRE(seq->getIsEmpty() == true);
    
    seq->append(23);
    REQUIRE(seq->getLength() == 1);
    REQUIRE(seq->getFirst() == 23);
    REQUIRE(seq->getLast() == 23);
    REQUIRE(seq->get(0) == 23);
    
    SECTION("Exceptions 1") {
        REQUIRE_THROWS_AS(seq->get(1), exception_outOfRange);
        REQUIRE_THROWS_AS(seq->get(-1), exception_outOfRange);
    }
    
    seq->append(43);
    REQUIRE(seq->getLength() == 2);
    REQUIRE(seq->getFirst() == 23);
    REQUIRE(seq->getLast() == 43);
    REQUIRE(seq->get(0) == 23);
    REQUIRE(seq->get(1) == 43);
    
    SECTION("Exceptions 2") {
        REQUIRE_THROWS_AS(seq->get(2), exception_outOfRange);
        REQUIRE_THROWS_AS(seq->get(-1), exception_outOfRange);
    }
    
    seq->prepend(53);
    REQUIRE(seq->getLength() == 3);
    REQUIRE(seq->getFirst() == 53);
    REQUIRE(seq->getLast() == 43);
    REQUIRE(seq->get(0) == 53);
    REQUIRE(seq->get(1) == 23);
    
    SECTION("Exceptions 3") {
        REQUIRE_THROWS_AS(seq->get(3), exception_outOfRange);
        REQUIRE_THROWS_AS(seq->get(-1), exception_outOfRange);
    }
    
    ArraySequence<int>* arr = new ArraySequence<int>;
    
    SECTION("Exception 4") {
        REQUIRE_THROWS_AS(arr = seq->getSubSequence(5, 3), exception_incorrectSelection);
    }
    
    arr = seq->getSubSequence(1, 1);
    REQUIRE(arr->getLength() == 1);
    REQUIRE(arr->getFirst() == 23);
    REQUIRE(arr->getLast() == 23);
}

TEST_CASE("ArraySequence test 2") {
    ArraySequence<int>* seq1 = new ArraySequence<int>(100, 10, 100);
    REQUIRE(seq1->getLength() == 100);
    ArraySequence<int>* seq2 = new ArraySequence<int>(seq1);
    REQUIRE(seq2->get(5) == seq2->get(5));
    ArraySequence<int>* seq3 = new ArraySequence<int>;
    
    SECTION("Exceptions (empty)") {
        REQUIRE_THROWS_AS(seq3->getFirst(), exception_sequenceIsEmpty);
        REQUIRE_THROWS_AS(seq3->getLast(), exception_sequenceIsEmpty);
    }
    
    seq3 = seq1->getSubSequence(40, 60);
    REQUIRE(seq3->get(0) == seq2->get(40));
}

TEST_CASE("ArraySequence test 3") {
    ArraySequence<int>* seq = new ArraySequence<int>(10, 10, 100);
    REQUIRE(seq->getLength() == 10);
    int buffer = seq->get(5);
    seq->remove(buffer);
    REQUIRE(seq->getLength() == 9);
    seq->insertAt(5, buffer + 10);
    REQUIRE(seq->getLength() == 10);
    REQUIRE(seq->get(5) == buffer + 10);
}

TEST_CASE("ListSequence test 1") {
    ListSequence<int>* seq = new ListSequence<int>;
    REQUIRE(seq->getIsEmpty() == true);
    
    seq->append(23);
    REQUIRE(seq->getLength() == 1);
    REQUIRE(seq->getFirst() == 23);
    REQUIRE(seq->getLast() == 23);
    REQUIRE(seq->get(0) == 23);
    
    SECTION("Exceptions 1") {
        REQUIRE_THROWS_AS(seq->get(1), exception_outOfRange);
        REQUIRE_THROWS_AS(seq->get(-1), exception_outOfRange);
    }
    
    seq->append(43);
    REQUIRE(seq->getLength() == 2);
    REQUIRE(seq->getFirst() == 23);
    REQUIRE(seq->getLast() == 43);
    REQUIRE(seq->get(0) == 23);
    REQUIRE(seq->get(1) == 43);
    
    SECTION("Exceptions 2") {
        REQUIRE_THROWS_AS(seq->get(2), exception_outOfRange);
        REQUIRE_THROWS_AS(seq->get(-1), exception_outOfRange);
    }
    
    seq->prepend(53);
    REQUIRE(seq->getLength() == 3);
    REQUIRE(seq->getFirst() == 53);
    REQUIRE(seq->getLast() == 43);
    REQUIRE(seq->get(0) == 53);
    REQUIRE(seq->get(1) == 23);
    
    SECTION("Exceptions 3") {
        REQUIRE_THROWS_AS(seq->get(3), exception_outOfRange);
        REQUIRE_THROWS_AS(seq->get(-1), exception_outOfRange);
    }
    
    ListSequence<int>* arr = new ListSequence<int>;
    
    SECTION("Exception 4") {
        REQUIRE_THROWS_AS(arr = seq->getSubSequence(5, 3), exception_incorrectSelection);
    }
    
    arr = seq->getSubSequence(1, 1);
    REQUIRE(arr->getLength() == 1);
    REQUIRE(arr->getFirst() == 23);
    REQUIRE(arr->getLast() == 23);
}

TEST_CASE("ListSequence test 2") {
    ListSequence<int>* seq1 = new ListSequence<int>(100, 10, 100);
    REQUIRE(seq1->getLength() == 100);
    ListSequence<int>* seq2 = new ListSequence<int>(seq1);
    REQUIRE(seq2->get(5) == seq2->get(5));
    ListSequence<int>* seq3 = new ListSequence<int>;
    
    SECTION("Exceptions (empty)") {
        REQUIRE_THROWS_AS(seq3->getFirst(), exception_sequenceIsEmpty);
        REQUIRE_THROWS_AS(seq3->getLast(), exception_sequenceIsEmpty);
    }
    
    seq3 = seq1->getSubSequence(40, 60);
    REQUIRE(seq3->get(0) == seq2->get(40));
}

TEST_CASE("ListSequence test 3") {
    ListSequence<int>* seq = new ListSequence<int>(10, 10, 100);
    REQUIRE(seq->getLength() == 10);
    int buffer = seq->get(5);
    seq->remove(buffer);
    REQUIRE(seq->getLength() == 9);
    seq->insertAt(5, buffer + 10);
    REQUIRE(seq->getLength() == 10);
    REQUIRE(seq->get(5) == buffer + 10);
}
