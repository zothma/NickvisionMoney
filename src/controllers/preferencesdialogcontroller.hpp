#pragma once

#include "../models/configuration.hpp"

namespace NickvisionMoney::Controllers
{
	/**
	 * A controller for PreferencesDialog
	 */
	class PreferencesDialogController
	{
	public:
		/**
		 * Constructs a PreferencesDialogController
		 *
		 * @param configuration The configuration fot the application (Stored as reference)
		 */
		PreferencesDialogController(NickvisionMoney::Models::Configuration& configuration);
		/**
		 * Gets the theme from the configuration as an int
		 *
		 * @returns The theme from the configuration as an int
		 */
		int getThemeAsInt() const;
		/**
		 * Sets the theme in the configuration
		 *
		 * @param theme The new theme as an int
		 */
		void setTheme(int theme);
		/**
		 * Gets the currency symbol to use when displaying monetary values
		 *
		 * @returns The currency symbol to use when displaying monetary values
		 */
		const std::string& getCurrencySymbol() const;
		/**
		 * Sets the currency symbol to use when displaying monetary values
		 *
		 * @param currencySymbol The new currency symbol to use when displaying monetary values
		 */
		void setCurrencySymbol(const std::string& currencySymbol);
		/**
		 * Saves the configuration file
		 */
		void saveConfiguration() const;

	private:
		NickvisionMoney::Models::Configuration& m_configuration;
	};
}