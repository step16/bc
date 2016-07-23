#include "addressbook.h"

using std::string;

Contact::Contact(const string &name, const string &email)
    : name_(name), email_(email) {}

const string &Contact::name() const { return name_; }

const string &Contact::email() const { return email_; }

bool Contact::operator==(const Contact &a) const {
  return name_ == a.name_ && email_ == a.email_;
}

bool Contact::operator<(const Contact &a) const {
  if (name_ == a.name_) {
    return email_ < a.email_;
  }
  return name_ < a.name_;
}
