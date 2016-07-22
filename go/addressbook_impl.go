package addressbook

// bookImpl is a concrete implementation of AddressBook
type bookImpl WRITEME // TODO(step students): write this line.

func init() {
	New = func() AddressBook {
		return &bookImpl{}
	}
}

// Assert that bookImpl does actually implement AddressBook
var _ AddressBook = &bookImpl{}

// TODO(step students): write the remainder of this file.
// このファイルの残りの中身を書いてください！
