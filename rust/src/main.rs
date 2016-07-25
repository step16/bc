#![feature(btree_range, collections_bound)]

use std::collections::Bound::{Excluded, Unbounded};
use std::collections::BTreeMap;
use std::collections::btree_map::Entry::{Occupied, Vacant};

#[derive(Debug, Eq, PartialEq, Clone, Ord, PartialOrd)]
struct Contact {
    name: String,
    email: String,
}

impl Contact {
    pub fn new(name: &str, email: &str) -> Contact {
        Contact {
            name: name.to_string(),
            email: email.to_string(),
        }
    }
}

trait AddressBook {
    fn new() -> Self;
    fn insert(&mut self, contact: Contact) -> bool;
    fn find_by_name(&self, name: &str) -> Option<&Contact>;
    fn find_by_email(&self, email: &str) -> Option<&Contact>;
    fn find_next(&self, contact: &Contact) -> Option<&Contact>;
    fn delete(&mut self, contact: &Contact) -> bool;
}

struct MyAddressBook {
    name_map: BTreeMap<String, Contact>,
    email_map: BTreeMap<String, Contact>,
}

impl AddressBook for MyAddressBook {
    fn new() -> Self {
        MyAddressBook {
            email_map: BTreeMap::new(),
            name_map: BTreeMap::new(),
        }
    }
    fn insert(&mut self, c: Contact) -> bool {
        if let Vacant(e1) = self.name_map.entry(c.name.clone()) {
            if let Vacant(e2) = self.email_map.entry(c.name.clone()) {
                e1.insert(c.clone());
                e2.insert(c);
                true
            } else {
                false
            }
        } else {
            false
        }
    }
    fn find_by_name(&self, name: &str) -> Option<&Contact> {
        self.name_map.get(name)
    }
    fn find_by_email(&self, email: &str) -> Option<&Contact> {
        self.email_map.get(email)
    }
    fn find_next(&self, c: &Contact) -> Option<&Contact> {
        self.name_map.range(Excluded(&c.name), Unbounded::<&str>).next().map(|(_, v)| v)
    }
    fn delete(&mut self, c: &Contact) -> bool {
        if let Occupied(e1) = self.name_map.entry(c.name.clone()) {
            if let Occupied(e2) = self.email_map.entry(c.name.clone()) {
                e1.remove();
                e2.remove();
                true
            } else {
                false
            }
        } else {
            false
        }
    }
}

#[cfg(test)]
mod tests {
    use super::{AddressBook, Contact, MyAddressBook};

    fn insert_test<T: AddressBook>() {
        let mut book = T::new();
        assert!(book.find_next(&Contact::new("a", "world@mail.com")).is_none());

        assert!(book.find_by_name("hello").is_none());
        assert!(book.insert(Contact::new("hello", "world@mail.com")));
        assert!(!book.insert(Contact::new("hello", "world@mail.com")));

        assert_eq!(book.find_next(&Contact::new("a", "world@mail.com")).unwrap(),
                   &Contact::new("hello", "world@mail.com"));
        assert!(book.find_next(&Contact::new("z", "world@mail.com")).is_none());

        {
            let contact = book.find_by_name("hello");
            assert!(contact.is_some());
            assert_eq!(contact.unwrap().name, "hello");
            assert_eq!(contact.unwrap().email, "world@mail.com");
        }
        assert!(book.delete(&Contact::new("hello", "world@mail.com")));
        assert!(book.find_by_name("hello").is_none());
    }

    // TODO(hayato): Write other tests.

    #[test]
    fn test() {
        insert_test::<MyAddressBook>();
    }
}

fn main() {
    println!("Hello, World!");
}
