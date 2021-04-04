#include "Table.h"

#include <gtest.h>

TEST(UnsortedTable, can_find_key_place) {
	UnsortedTable<int> t;
	t.insert(0, 1);
	t.insert(5, 10);
	ASSERT_EQ(1, t.find_key(5));
}

TEST(UnsortedTable, can_insert_element) {
	UnsortedTable<int> t;
	ASSERT_NO_THROW(t.insert(0, 1));
}

TEST(UnsortedTable, cant_insert_existing_element) {
	UnsortedTable<int> t;
	t.insert(0, 1);
	ASSERT_ANY_THROW(t.insert(0, 2));
}  

TEST(UnsortedTable, insert_change_size) {
	UnsortedTable<int> t;
	t.insert(0, 1);
	ASSERT_EQ(1, t.GetSize());
}

TEST(UnsortedTable, empty_table) {
	UnsortedTable<int> t;
	ASSERT_EQ(1, t.IsEmpty());
}

TEST(UnsortedTable, can_erase_element) {
	UnsortedTable<int> t;
	t.insert(0, 1);
	ASSERT_NO_THROW(t.erase(0));
}

TEST(UnsortedTable, cant_erase_element_from_empty_table) {
	UnsortedTable<int> t;
	ASSERT_ANY_THROW(t.erase(5));
}

TEST(UnsortedTable, cant_erase_non_existent_element) {
	UnsortedTable<int> t;
	t.insert(0, 1);
	ASSERT_ANY_THROW(t.erase(5));
}

TEST(UnsortedTable, erase_change_size) {
	UnsortedTable<int> t;
	t.insert(0, 1);
	t.erase(0);
	ASSERT_EQ(0, t.GetSize());
}

TEST(UnsortedTable, can_clear_unsorted_table) {
	UnsortedTable<int> t;
	t.insert(0, 1);
	t.clear();
	ASSERT_EQ(0, t.GetSize());
}

TEST(SortedTable, can_find_key_place) {
	SortedTable<int> t;
	t.insert(0, 1);
	t.insert(5, 10);
	t.insert(3, 10);
	ASSERT_EQ(2, t.find_key(5));
}

TEST(SortedTable, can_insert_element) {
	SortedTable<int> t;
	ASSERT_NO_THROW(t.insert(0, 1));
}

TEST(SortedTable, cant_insert_existing_element) {
	SortedTable<int> t;
	t.insert(0, 1);
	ASSERT_ANY_THROW(t.insert(0, 2));
}

TEST(SortedTable, insert_change_size) {
	SortedTable<int> t;
	t.insert(0, 1);
	ASSERT_EQ(1, t.GetSize());
}

TEST(SortedTable, insert_element_to_correct_place) {
	SortedTable<int> t;
	t.insert(0, 1);
	t.insert(3, 1);
	t.insert(2, 1);
	ASSERT_EQ(1, t.find_key(2));
}

TEST(SortedTable, can_erase_element) {
	SortedTable<int> t;
	t.insert(0, 1);
	ASSERT_NO_THROW(t.erase(0));
}

TEST(SortedTable, cant_erase_element_from_empty_table) {
	SortedTable<int> t;
	ASSERT_ANY_THROW(t.erase(5));
}

TEST(SortedTable, cant_erase_non_existent_element) {
	SortedTable<int> t;
	t.insert(0, 1);
	ASSERT_ANY_THROW(t.erase(5));
}

TEST(SortedTable, erase_change_size) {
	SortedTable<int> t;
	t.insert(0, 1);
	t.erase(0);
	ASSERT_EQ(0, t.GetSize());
}

TEST(SortedTable, can_clear_sorted_table) {
	SortedTable<int> t;
	t.insert(0, 1);
	t.clear();
	ASSERT_EQ(0, t.GetSize());
}



 