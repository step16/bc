package addressbook

// Contact describes an individual contact with a Name and Email
// address.
type Contact struct {
	Name, Email string
}

// AddressBook provides functions to insert, search, and delete
// contacts.
type AddressBook interface {
	// Insert inserts the specified contact into the address book.  If
	// there's already a contact with the same name or email, the
	// insertion fails and false is returned.
	Insert(Contact) bool

	// FindName looks up a contact by the specified name.  If no such
	// name is found, it returns nil. The pointer returned may be to a
	// copy of the original.
	FindName(string) *Contact

	// FindEmail looks up a contact by the specified email address.  If
	// no such email address is found, it returns nil. The pointer
	// returned may be to a copy of the original.
	FindEmail(string) *Contact

	// FindNext returns a pointer to the contact that comes
	// lexicographically after the given contact. It returns nil if
	// there are no more contacts.
	FindNext(Contact) *Contact

	// Delete deletes the specified contact. Returns true iff the given
	// contact was actually deleted.
	Delete(Contact) bool
}

// New creates a new AddressBook. This should be set to a function
// that returns a value that implements AddressBook.
var New func() AddressBook

// Less defines a lexicographical order over contacts where contacts
// are sorted first by Name, then by Email.
func (c1 Contact) Less(c2 Contact) bool {
	if c1.Name == c2.Name {
		return c1.Email < c2.Email
	}
	return c1.Name < c2.Name
}
