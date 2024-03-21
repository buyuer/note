pub trait Animal {
    fn eat();
    fn run();
}

#[derive(Debug)]
pub struct Person {
    name: String,
    age: i32,
    label: Vec<String>,
}

impl Animal for Person {
    fn eat() {
        todo!()
    }

    fn run() {
        todo!()
    }
}

impl Person {
    fn new() -> Self {
        Person {
            name: "".to_string(),
            age: 0,
            label: vec![],
        }
    }
}