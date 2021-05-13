#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Transaction
{
public:
	Transaction(
		unsigned int payerID, unsigned int recipientID,
		double amount, std::string comment = ""
	)
		: m_payerID { payerID }, m_recipientID { recipientID },
		  m_amount { amount }, m_comment { comment }
	{
		if (m_payerID == m_recipientID)
		{
			std::cout <<
				"Invalid transaction: Payer and recipient should not be the "
				"same.\n";
		}
	}

	void print(const std::vector<std::string>& names)
	{
		std::cout << "Payer: " << names[m_payerID] << '\t'
			<< "Recipient: " << names[m_recipientID] << '\t'
			<< "Amount: " << m_amount << '\n';

		if (m_comment != "")
			std::cout << "\tComment: " << m_comment << '\n';
	}

	const unsigned int m_payerID;
	const unsigned int m_recipientID;
	const double m_amount;

private:
	const std::string m_comment;
};

class Ledger
{
public:
	Ledger(): m_names {}, m_transactions {}
	{
	}

	void addTransaction(
		const std::string payerName, const std::string recipientName,
		const double amount, const std::string comment
	)
	{
		m_transactions.push_back(
			Transaction{
				getID(payerName), getID(recipientName), amount, comment
			}
		);
	}

	void getTransactionFromUser()
	{
		std::cout << "Name of payer: ";
		std::string payerName { "" };
		std::cin >> payerName;

		std::cout << "Name of recipient: ";
		std::string recipientName { "" };
		std::cin >> recipientName;

		if (payerName == recipientName)
		{
			std::cout <<
				"Payer and recipient should not be the same. Try again.\n";
			return;
		}

		std::cout << "Amount: ";
		double amount { 0.0 };
		std::cin >> amount;

		if (amount <= 0.0)
		{
			std::cout << "Amount should be positive. Try again.\n";
			return;
		}

		std::cout << "Comment: ";
		std::string comment { "" };
		// Clear buffer up to and including a \n
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, comment);

		addTransaction(payerName, recipientName, amount, comment);
	}

	void printTransactions()
	{
		if (m_transactions.size() == 0)
		{
			std::cout << "No transactions\n";
			return;
		}

		for (Transaction trans : m_transactions)
			trans.print(m_names);
	}

	std::vector<double> calculateBalances()
	{
		std::vector<double> balance(m_names.size());

		for (Transaction trans : m_transactions)
		{
			balance[trans.m_payerID] += trans.m_amount;
			balance[trans.m_recipientID] -= trans.m_amount;
		}

		return balance;
	}

	std::vector<Transaction> settle()
	{
		if (m_names.size() == 0)
		{
			std::cout << "Nothing to settle\n";
			return std::vector<Transaction>{ };
		}

		std::vector<double> balance { calculateBalances() };

		std::vector<Transaction> inverseTransactions { };

		// With this algorithm, the maximum number of transactions required to
		// settle is m_names.size() -1
		for (unsigned int i = 0; i < m_names.size() - 1; ++i)
		{
			auto maxBalance {
				std::max_element(balance.begin(), balance.end())
			};
			// If all balances are settled already, we can end the loop
			if (*maxBalance < 1e-3)
			{
				std::cout << "settle(): Fewer transactions needed\n";
				break;
			}

			auto minBalance {
				std::min_element(balance.begin(), balance.end())
			};

			if (*maxBalance > std::abs(*minBalance))
			{
				inverseTransactions.push_back(
					Transaction{
						static_cast<unsigned int>(maxBalance - balance.begin()),
						static_cast<unsigned int>(minBalance - balance.begin()),
						std::abs(*minBalance)
					}
				);

				*maxBalance -= std::abs(*minBalance);
				*minBalance = 0.0;
			}
			else
			{
				inverseTransactions.push_back(
					Transaction{
						static_cast<unsigned int>(maxBalance - balance.begin()),
						static_cast<unsigned int>(minBalance - balance.begin()),
						*maxBalance
					}
				);

				*minBalance += *maxBalance;
				*maxBalance = 0.0;
			}
		}

		for (Transaction trans : inverseTransactions)
			trans.print(m_names);

		return inverseTransactions;
	}

private:
	unsigned int getID(std::string name)
	{
		// Check if name is already in m_names
		auto found { std::find(m_names.begin(), m_names.end(), name) };

		// If it is, the person already has an ID
		if (found != m_names.end())
		{
			// Return index of the name in m_names
			return found - m_names.begin();
		}
		// If it is not, add the name to m_names and return new ID
		else
		{
			m_names.push_back(name);
			// New ID is the index of last element
			return m_names.size() - 1;
		}
	}

	// Array of names of the people involved. ID = i corresponds to m_names[i]
	std::vector<std::string> m_names;

	std::vector<Transaction> m_transactions;
};

void printListOfCommands()
{
	std::cout <<
		"a\tAdd a transaction to the ledger\n"
		"c\tPrint a list of accepted commands\n"
		"p\tPrint all transactions in the ledger\n"
		"q\tQuit program\n"
		"s\tSettle the current balances\n";
}

int main()
{
	Ledger ledger;

	// ledger.addTransaction("Alice", "Bob", 12.4, "For ticket");
	// ledger.addTransaction("Charlie", "Alice", 33.28, "For pizza");
	// ledger.addTransaction("Diana", "Charlie", 15.6, "");
	// ledger.addTransaction("Bob", "Charlie", 8.55, "");
	// ledger.addTransaction("Alice", "Diana", 21.63, "");
	// ledger.addTransaction("Charlie", "Bob", 27.11, "");
	// ledger.addTransaction("Diana", "Charlie", 16.84, "");
	// ledger.addTransaction("Alice", "Emilia", 5.42, "");
	// ledger.addTransaction("Diana", "Emilia", 10.67, "");
	// ledger.addTransaction("Emilia", "Charlie", 22.58, "");
	// // ledger.printTransactions();
	// ledger.settle();

	std::cout <<
		"pridivide version 0.0\n"
		"Type 'c' for a list of commands\n";
	while (true)
	{
		// Print prompt
		std::cout << "\033[92m(pridivide)\033[0m ";
		char input { '\0' };
		std::cin >> input;

		switch (input)
		{
			case 'a':
				ledger.getTransactionFromUser();
				break;
			case 'c':
				printListOfCommands();
				break;
			case 'p':
				ledger.printTransactions();
				break;
			case 'q':
				return 0;
			case 's':
				ledger.settle();
				break;
		}
	}

	return 0;
}
