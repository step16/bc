#include <utility>
#include <string>

// Contact describes a single Contact that might be in an
// AddressBook. A contact contains a name and email address, and is
// immutable.
class Contact {
public:
  Contact(const std::string &name, const std::string &email);
  const std::string &name() const;
  const std::string &email() const;
  bool operator==(const Contact &a) const;
  bool operator<(const Contact &a) const;

private:
  std::string name_;
  std::string email_;
};

// AddressBook describes a collection of Contacts. Contacts can be
// Inserted, and Deleted,
class AddressBook {
public:
  // Destructor doesn't have to do anything.
  virtual ~AddressBook() {}

  // Insert inserts the specified contact into the address book.  If
  // there's already a contact with the same name or email, the
  // insertion fails and false is returned.
  virtual bool Insert(const Contact &) = 0;

  // FindEmail looks up a contact by the specified email address.
  // If no such email address is found, it returns nullptr.
  virtual const Contact *FindEmail(const std::string &email) const = 0;

  // FindName looks up a contact by the specified name.
  // If no such name is found, it returns nullptr.
  virtual const Contact *FindName(const std::string &name) const = 0;

  // FindNext returns a pointer to the contact that comes
  // lexicographically after the given contact. It returns nullptr if
  // there are no more contacts.
  virtual const Contact *FindNext(const Contact &) const = 0;

  // Delete deletes the specified contact. Returns true iff the given
  // contact was actually deleted.
  virtual bool Delete(const Contact &) = 0;
};
