#include <iostream>
#include <sstream>
#include <benchmark/benchmark.h>

#include "addressbook-impl.h"

using namespace std;

class AddressBench : public benchmark::Fixture {
public:
  virtual ~AddressBench() {}

  string FakeX(const string &base, int i) const {
    ostringstream os;
    os << "Fake " << base << " " << i;
    return os.str();
  }
  string FakeName(int i) const { return FakeX("Name", i); }
  string FakeEmail(int i) const { return FakeX("Email", i); }
  Contact FakeContact(int i) const {
    return Contact(FakeName(i), FakeEmail(i));
  }

  AddressBook *NewBook() { return new MyAddressBook; }
};

BENCHMARK_DEFINE_F(AddressBench, InsertOnly)(benchmark::State &st) {
  size_t ops = 0;
  while (st.KeepRunning()) {
    auto book = NewBook();
    for (int i = 0; i < st.range_x(); ++i) {
      book->Insert(FakeContact(i));
      ++ops;
    }
    delete book;
  }
  st.SetItemsProcessed(ops);
}

BENCHMARK_REGISTER_F(AddressBench, InsertOnly)->Range(8, 8 << 10);

BENCHMARK_DEFINE_F(AddressBench, LookupOnly)(benchmark::State &st) {
  // Insert a bunch of data.
  auto book = NewBook();
  for (int i = 0; i < st.range_x(); ++i) {
    book->Insert(FakeContact(i));
  }

  // Search for a lot of them.
  size_t ops = 0;
  while (st.KeepRunning()) {
    book->FindName(FakeName(rand() % (st.range_x() * 2)));
    book->FindEmail(FakeEmail(rand() % (st.range_x() * 2)));
    ++ops;
  }
  st.SetItemsProcessed(ops);
  delete book;
}

BENCHMARK_REGISTER_F(AddressBench, LookupOnly)->Range(8, 8 << 10);

BENCHMARK_DEFINE_F(AddressBench, Mixed)(benchmark::State &st) {
  size_t ops = 0;
  while (st.KeepRunning()) {
    auto book = NewBook();
    // Insert a bunch of data.
    for (int i = 0; i < st.range_x(); ++i) {
      book->Insert(FakeContact(i));
      ++ops;
    }
    // Insert more, search for some, delete one at random.
    for (int i = 0; i < st.range_x(); ++i) {
      book->Insert(FakeContact(i + st.range_x()));
      book->FindName(FakeName(rand() % (st.range_x() * 2)));
      book->FindEmail(FakeEmail(rand() % (st.range_x() * 2)));
      book->Delete(FakeContact(rand() % st.range_x()));
      ++ops;
    }
    delete book;
  }
  st.SetItemsProcessed(ops);
}

BENCHMARK_REGISTER_F(AddressBench, Mixed)->Range(8, 8 << 10);

BENCHMARK_DEFINE_F(AddressBench, FindNext)(benchmark::State &st) {
  auto book = NewBook();
  // Insert a bunch of data.
  for (int i = 0; i < st.range_x(); ++i) {
    book->Insert(FakeContact(i));
  }

  size_t ops = 0;
  while (st.KeepRunning()) {
    book->FindNext(FakeContact(rand() % st.range_x()));
    ++ops;
  }
  delete book;
  st.SetItemsProcessed(ops);
}

BENCHMARK_REGISTER_F(AddressBench, FindNext)->Range(8, 8 << 10);

BENCHMARK_MAIN();
