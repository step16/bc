package addressbook

import (
	"fmt"
	"math/rand"
	"testing"
)

var (
	arthur = Contact{
		Name:  "Arthur Dent",
		Email: "adent@cottington",
	}
	ford = Contact{
		Name:  "Ford Prefect",
		Email: "froopy-dude@greater-betelgeuse",
	}
	trillian = Contact{
		Name:  "Tricia McMillan",
		Email: "trillian@heart.of.gold",
	}
	zaphod = Contact{
		Name:  "Zaphod Beeblebrox",
		Email: "prez@galaxy",
	}
)

func TestEmpty(t *testing.T) {
	book := New()
	if got := book.FindName(arthur.Name); got != nil {
		t.Errorf("FindName(%q) got %v, wanted nil", arthur.Name, got)
	}
}

func TestInsertLookup(t *testing.T) {
	book := New()
	for _, in := range []Contact{arthur, ford} {
		if !book.Insert(in) {
			t.Errorf("Insert(%v) got false, wanted true", ford)
		}
		if got := book.FindName(in.Name); got == nil || *got != in {
			t.Errorf("FindName(%q) got %v, wanted %v", in.Name, got, in)
		}
		if got := book.FindEmail(in.Email); got == nil || *got != in {
			t.Errorf("FindEmail(%q) got %v, wanted %v", in.Email, got, in)
		}
	}
}

func TestInsertDuplicate(t *testing.T) {
	book := New()
	book.Insert(Contact{"Marvin", "marvin@scc"})
	if book.Insert(Contact{"Marvin", "marvin@sirius-corp"}) {
		t.Errorf("Insert(different email) got true, wanted false")
	}
	if book.Insert(Contact{"Marvin the Paranoid Android", "marvin@scc"}) {
		t.Errorf("Insert(different name) got true, wanted false")
	}
}

func TestFindNext(t *testing.T) {
	book := New()
	for _, tc := range []struct {
		name    string
		inserts []Contact
		in      Contact
		want    *Contact // want might be nil
	}{{
		name:    "in order insertion",
		inserts: []Contact{trillian, zaphod},
		in:      trillian,
		want:    &zaphod,
	}, {
		name:    "out of order insertion",
		inserts: []Contact{zaphod, trillian},
		in:      trillian,
		want:    &zaphod,
	}, {
		name:    "end of book",
		inserts: []Contact{trillian, zaphod},
		in:      zaphod,
		want:    nil,
	}} {
		for _, c := range tc.inserts {
			book.Insert(c)
		}
		got := book.FindNext(tc.in)
		if (got == nil) != (tc.want == nil) {
			t.Errorf("%s: after inserting %v, FindNext(%v) got %v, wanted %v", tc.name, tc.inserts, tc.in, tc.want)
			continue
		}
		if tc.want == nil {
			continue
		}
		if got.Name != tc.want.Name {
			t.Errorf("%s: after inserting %v, FindNext(%v) got %v, wanted %v", tc.name, tc.inserts, tc.in, tc.want)
		}
	}
}

// Benchmarks

func fakeContact(i int) Contact {
	return Contact{
		Name:  fmt.Sprintf("Fake Name %d", i),
		Email: fmt.Sprintf("Fake-%d@email", i),
	}
}

const kBookSize = 4096

func BenchmarkInsertOnly(b *testing.B) {
	for i := 0; i < b.N; i++ {
		book := New()
		for j := 0; j < kBookSize; j++ {
			book.Insert(fakeContact(j))
		}
	}
}

func BenchmarkInsertLookup(b *testing.B) {
	for i := 0; i < b.N; i++ {
		book := New()
		// Add lots of contacts
		for j := 0; j < kBookSize; j++ {
			book.Insert(fakeContact(j))
		}
		// Lookup lots all the contacts
		for j := 0; j < kBookSize; j += 2 {
			book.FindName(fakeContact(j).Name)
			book.FindEmail(fakeContact(j + 1).Email)
		}
	}
}

func BenchmarkMix(b *testing.B) {
	for i := 0; i < b.N; i++ {
		book := New()
		// Add lots of contacts
		for j := 0; j < kBookSize; j++ {
			book.Insert(fakeContact(j))
		}

		for j := 0; j < kBookSize; j += 2 {
			// insert one more
			book.Insert(fakeContact(kBookSize + j))
			// look some up
			book.FindName(fakeContact(rand.Intn(kBookSize)).Name)
			book.FindEmail(fakeContact(rand.Intn(kBookSize)).Email)
			// delete one
			book.Delete(fakeContact(rand.Intn(kBookSize)))
		}
	}
}
