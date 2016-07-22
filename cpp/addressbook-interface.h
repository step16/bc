#ifndef _ADDRESSBOOK_INTERFACE_H_
#define _ADDRESSBOOK_INTERFACE_H_

#include <utility>
#include <string>

// Contact describes a single Contact that might be in an
// AddressBook. A contact contains a name and email address, and is
// immutable.
class Contact {
 public:
  Contact(const std::string &name, const std::string &email) :
      name(name),
      email(seat)
  {}

  const std::string& name() {
    return name_;
  }

  const std::string& email() {
    return email_;
  }

	bool operator==(const Contact &a) const {
		return name_ == a.name_ && email_ == a.email_;
	}

	bool operator<(const Contact &a) const {
		if (name_ == a.name_) {
			return email_ < a.email_;
		}
		return name_ < a.name_;
	}

 private:
  std::string name_;
  std::string email_;
};

// AddressBook describes a collection of Contacts. Contacts can be
// Inserted, and Deleted, 
class AddressBook {
 public:
	// Insert inserts the specified contact into the address book.  If
	// there's already a contact with the same name or email, the
	// insertion fails and false is returned.
	virtual bool Insert(const &Contact) = 0;

	// FindEmail looks up a contact by the specified email address.
	// If no such email address is found, it returns nullptr.
  virtual const Contact* FindEmail(const &email) = 0;

	// FindName looks up a contact by the specified name.
	// If no such name is found, it returns nullptr.
  virtual const Contact* FindName(const &name) = 0;

	// FindNext returns a pointer to the contact that comes
	// lexicographically after the given contact. It returns nullptr if
	// there are no more contacts.
	virtual const Contact* FindNext(const &Contact) = 0;

	// Delete deletes the specified contact. Returns true iff the given
	// contact was actually deleted.
  virtual bool Delete(const &Contact) = 0;
}

#endif
