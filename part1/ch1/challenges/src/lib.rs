// challenges:

// 1. implement identity function

fn id<T>(x: T) -> T {
    x
}

// 2. implement composition function

fn compose<A, B, C, G, F>(g: G, f: F) -> impl Fn(A) -> C
where
    F: Fn(A) -> B,
    G: Fn(B) -> C,
{
    move |x| g(f(x)) //'move' captures environment of closure
}

// 3. test composition respects identity

fn square(x: usize) -> usize {
    x * x
}

#[test]
fn test_square_circ_id() {
    assert_eq!(square(4), compose(square, id)(4));
}

#[test]
fn test_id_circ_square() {
    assert_eq!(square(7), compose(id, square)(7));
}

// 4. is the world wide web a category? are the links morphisms?

// 5. is facebook a category, with people objects and friendships morphisms?

// 6. when is a directed graph a category?
