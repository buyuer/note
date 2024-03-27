//
pub trait Biology {
    fn is_live() -> bool;
}

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

impl Person {
    fn new() -> Self {
        Person {
            name: "".to_string(),
            age: 0,
            label: vec![],
        }
    }
}

impl Biology for Person {
    fn is_live() -> bool {
        todo!()
    }
}

impl Animal for Person {
    fn eat() {
        todo!()
    }

    fn run() {
        todo!()
    }
}


enum Color {
    RED,
    BLUE,
    BLACK,
    WRITE,
}

pub struct Dog {
    name: String,
    color: Color,
}

pub struct Cat(String, Color);