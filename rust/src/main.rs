use std::collections::BTreeMap;

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
        MyAddressBook { email_map: BTreeMap::new(), name_map: BTreeMap::new() }
    }
    fn insert(&mut self, contact: Contact) -> bool {
        if self.name_map.contains_key(&contact.name) {
            false
        } else if self.email_map.contains_key(&contact.email) {
            false
        } else {
            assert_eq!(self.name_map.insert(contact.name.clone(), contact.clone()), None);
            assert_eq!(self.email_map.insert(contact.email.clone(), contact), None);
            true
        }
    }
    fn find_by_name(&self, name: &str) -> Option<&Contact> {
        self.name_map.get(name)
    }
    fn find_by_email(&self, email: &str) -> Option<&Contact> {
        self.email_map.get(email)
    }
    fn find_next(&self, _: &Contact) -> Option<&Contact> {
        // BTreeMap.range is unstable in rust stable channel. Just skip it. :)
        // self.name_map.range(Excluded::<&str>(&c.name), Unbounded).next().map(|e| e.1)
        unimplemented!();
    }
    fn delete(&mut self, c: &Contact) -> bool {
        if self.name_map.contains_key(&c.name) && self.email_map.contains_key(&c.email) {
            self.name_map.remove(&c.name);
            self.email_map.remove(&c.email);
            true
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
	assert!(book.find_by_name("hello").is_none());
	assert!(book.insert(Contact::new("hello", "world@mail.com")));
	assert!(!book.insert(Contact::new("hello", "world@mail.com")));
        {
	    let contact = book.find_by_name("hello");
	    assert!(contact.is_some());
	    assert_eq!(contact.unwrap().name, "hello");
	    assert_eq!(contact.unwrap().email, "world@mail.com");
        }
	assert!(book.delete(&Contact::new("hello", "world@mail.com")));
	// assert!(book.find_by_name("hello").is_none());
    }

    #[test]
    fn test() {
        insert_test::<MyAddressBook>();
    }
}

fn main() {
    println!("Hello, World!");
}
