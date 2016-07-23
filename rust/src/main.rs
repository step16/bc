#![allow(dead_code)]
#![allow(unused_variables)]

#[derive(Debug, Eq, PartialEq, Clone, Ord, PartialOrd)]
struct Contact {
    name: String,
    email: String,
}

impl Contact {
    pub fn new(name: &str, email: &str) -> Contact {
        Contact { name: name.to_string(), email: email.to_string() }
    }
}

trait AddressBook {
    fn new() -> Self;
    fn insert(&mut self, contact: Contact) -> bool;
    fn find_by_email(&self, email: &str) -> Option<&Contact>;
    fn find_by_name(&self, name: &str) -> Option<&Contact>;
    fn find_next(&self, contact: &Contact) -> Option<&Contact>;
    fn delete(&mut self, contact: &Contact) -> bool;
}

struct MyAddressBook {
}

impl AddressBook for MyAddressBook {
    fn new() -> Self {
        unimplemented!()
    }
    fn insert(&mut self, contact: Contact) -> bool {
        unimplemented!()
    }
    fn find_by_email(&self, email: &str) -> Option<&Contact> {
        unimplemented!()
    }
    fn find_by_name(&self, name: &str) -> Option<&Contact> {
        unimplemented!()
    }
    fn find_next(&self, contact: &Contact) -> Option<&Contact> {
        unimplemented!()
    }
    fn delete(&mut self, contaxt: &Contact) -> bool {
        unimplemented!()
    }
}

#[cfg(test)]
mod tests {
    use super::{AddressBook, Contact, MyAddressBook};

    fn insert_test<T: AddressBook>() {
        let mut book = T::new();
	assert!(book.find_by_name("hello").is_none());
	assert!(book.insert(Contact::new("hello", "world@mail.com")));
	assert!(!book.insert(Contact::new("hello", "world@mail.com")));
        {
	    let contact = book.find_by_name("hello");
	    assert!(contact.is_some());
	    assert_eq!(contact.unwrap().name, "hello");
	    assert_eq!(contact.unwrap().email, "world@mail.com");
        }
	book.delete(&Contact::new("hello", "world@mail.com"));
	assert!(book.find_by_name("hello").is_none());
    }

    #[test]
    fn test() {
        insert_test::<MyAddressBook>();
    }
}

fn main() {
    println!("Hello, World!");
}
