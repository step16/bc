#include <gtest/gtest.h>
#include "addressbook-impl.h"

using namespace std;

class AddressBookTest : public testing::Test {
public:
  AddressBookTest() : book_(new MyAddressBook) {}

  virtual ~AddressBookTest() { delete book_; }

  AddressBook *book_;
};

TEST_F(AddressBookTest, Single) {
  EXPECT_EQ(nullptr, book_->FindName("Arthur Dent"));
  EXPECT_TRUE(book_->Insert(Contact("Arthur Dent", "adent@cottington")));
  // insertion should only work once.
  EXPECT_FALSE(book_->Insert(Contact("Arthur Dent", "adent@demolished")));
  const Contact *contact = book_->FindName("Arthur Dent");
  ASSERT_NE(nullptr, contact);
  EXPECT_EQ("Arthur Dent", contact->name());
  EXPECT_EQ("adent@cottington", contact->email());
  book_->Delete(Contact("Arthur Dent", "adent@cottington"));
  EXPECT_EQ(nullptr, book_->FindName("Arthur Dent"));
}

TEST_F(AddressBookTest, Next) {
  book_->Insert(Contact("Tricia McMillan", "trillian@heart.of.gold"));
  book_->Insert(Contact("Zaphod Beeblebrox", "prez@galaxy"));
  const Contact *contact = book_->FindName("Tricia McMillan");
  ASSERT_NE(nullptr, contact);
  EXPECT_EQ("Tricia McMillan", contact->name());
  const Contact *next = book_->FindNext(*contact);
  ASSERT_NE(nullptr, next);
  EXPECT_EQ("prez@galaxy", next->email());
  EXPECT_EQ(nullptr, book_->FindNext(*next));
}

TEST_F(AddressBookTest, NextDeleted) {
  book_->Insert(Contact("Tricia McMillan", "trillian@heart.of.gold"));
  book_->Insert(Contact("Zaphod Beeblebrox", "prez@galaxy"));
  book_->Delete(Contact("Zaphod Beeblebrox", "prez@galaxy"));
  const Contact *contact = book_->FindName("Tricia McMillan");
  ASSERT_NE(nullptr, contact);
  ASSERT_EQ(nullptr, book_->FindNext(*contact));
}
