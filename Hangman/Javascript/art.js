function art(lives) {

    const ascii = [

        `
 + --- +
  |   |
      |
      |
      |
      |
=========`,
        `
  +---+
  |   |
  O   |
      |
      |
      |
=========`,
        `
  +---+
  |   |
  O   |
  |   |
      |
      |
=========`,
        `
  +---+
  |   |
  O   |
 /|   |
      |
      |
=========`,
        `
  +---+
  |   |
  O   |
 /|\  |
      |
      |
=========`,
        `
  +---+
  |   |
  O   |
 /|\  |
 /    |
      |
=========`,
        `
  +---+
  |   |
  O   |
 /|\  |
 / \  |
      |
=========`
    ]
    return ascii[6 - lives]
}

module.exports = art