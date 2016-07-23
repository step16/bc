#ifndef _ADDRESSBOOK_H_
#define _ADDRESSBOOK_H_

#include <vector>
#include "addressbook.h"

class MyAddressBook : public AddressBook {
public:
  bool Insert(const Contact &) override;
  const Contact *FindEmail(const std::string &email) const override;
  const Contact *FindName(const std::string &name) const override;
  const Contact *FindNext(const Contact &) const override;
  bool Delete(const Contact &) override;

  virtual ~MyAddressBook() {}

private:
  std::vector<Contact> contacts_;
};

#endif
