import gleam/erlang
import gleam/int
import gleam/io

// ----------------------------------------------------------------------------------------------

pub fn main() {
  game(0, 0)
}

// ----------------------------------------------------------------------------------------------

fn game(user_score: Int, computer_score: Int) {
  let results = round(user_score, computer_score)

  let print_score = fn(x: Int, y: Int) {
    io.println(
      "\nYour score: "
      <> int.to_string(x)
      <> " | Computer score: "
      <> int.to_string(y),
    )
  }
  print_score(results.0, results.1)

  let choice = take_input("\nAnother round?\n1) Continue\n2) Quit\n-> ")
  io.println("")
  case choice {
    "Rock" -> game(results.0, results.1)
    _ -> ""
  }
}

// ----------------------------------------------------------------------------------------------

fn round(user_score: Int, computer_score: Int) -> #(Int, Int) {
  let user =
    take_input("Enter your choice:\n1) Rock\n2) Paper\n3) Scissors\n-> ")
  let computer = computer_choice()

  let print = fn(x, y) {
    let text = "You picked: " <> x <> "\nComputer picked: " <> y
    io.println(text)
  }
  print(user, computer)

  let data = compare(user, computer)
  io.println(data.0)

  #(data.1 + user_score, data.2 + computer_score)
}

// ----------------------------------------------------------------------------------------------

fn take_input(prompt: String) -> String {
  let assert Ok(choice) = erlang.get_line(prompt)

  case choice {
    "1\n" -> "Rock"
    "2\n" -> "Paper"
    "3\n" -> "Scissors"
    _ -> take_input(prompt)
  }
}

// ----------------------------------------------------------------------------------------------

fn computer_choice() -> String {
  let computer = int.random(3)

  case computer {
    0 -> "Rock"
    1 -> "Paper"
    _ -> "Scissors"
  }
}

// ----------------------------------------------------------------------------------------------

fn compare(user: String, computer: String) -> #(String, Int, Int) {
  let inputs = #(user, computer)
  case inputs {
    #("Rock", "Paper") -> #("Computer wins", 0, 1)
    #("Rock", "Scissors") -> #("User wins", 1, 0)
    #("Scissors", "Rock") -> #("Computer wins", 0, 1)
    #("Scissors", "Paper") -> #("User wins", 1, 0)
    #("Paper", "Scissors") -> #("Computer wins", 0, 1)
    #("Paper", "Rock") -> #("User wins", 1, 0)
    _ -> #("Draw", 0, 0)
  }
}
// ----------------------------------------------------------------------------------------------
