#include "mainwindowcontroller.hpp"
#include <algorithm>
#include <ctime>
#include <filesystem>
#include "../helpers/translation.hpp"

using namespace NickvisionMoney::Controllers;
using namespace NickvisionMoney::Models;

MainWindowController::MainWindowController(AppInfo& appInfo, Configuration& configuration) : m_appInfo{ appInfo }, m_configuration{ configuration }, m_isOpened{ false }, m_isDevVersion{ m_appInfo.getVersion().find("-") != std::string::npos }
{

}

const AppInfo& MainWindowController::getAppInfo() const
{
    return m_appInfo;
}

bool MainWindowController::getIsDevVersion() const
{
    return m_isDevVersion;
}

PreferencesDialogController MainWindowController::createPreferencesDialogController() const
{
    return { m_configuration };
}

void MainWindowController::registerSendToastCallback(const std::function<void(const std::string& message)>& callback)
{
    m_sendToastCallback = callback;
}

void MainWindowController::startup()
{
    if(!m_isOpened)
    {
        m_isOpened = true;
    }
}

std::string MainWindowController::getWelcomeMessage() const
{
    std::time_t timeNow{ std::time(nullptr) };
    int timeNowHours{ std::localtime(&timeNow)->tm_hour };
    if(timeNowHours >= 0 && timeNowHours < 6)
    {
        return pgettext("Night", "Good Morning!");
    }
    else if(timeNowHours >= 6 && timeNowHours < 12)
    {
        return pgettext("Morning", "Good Morning!");
    }
    else if(timeNowHours >= 12 && timeNowHours < 18)
    {
        return _("Good Afternoon!");
    }
    else if(timeNowHours >= 18 && timeNowHours < 24)
    {
        return _("Good Evening!");
    }
    else
    {
        return _("Good Day!");
    }
}

std::vector<std::string> MainWindowController::getRecentAccounts() const
{
    std::vector<std::string> recentAccounts;
    if(std::filesystem::exists(m_configuration.getRecentAccount1()))
    {
        recentAccounts.push_back(m_configuration.getRecentAccount1());
    }
    if(std::filesystem::exists(m_configuration.getRecentAccount2()))
    {
        recentAccounts.push_back(m_configuration.getRecentAccount2());
    }
    if(std::filesystem::exists(m_configuration.getRecentAccount3()))
    {
        recentAccounts.push_back(m_configuration.getRecentAccount3());
    }
    return recentAccounts;
}

void MainWindowController::registerAccountAddedCallback(const std::function<void()>& callback)
{
    m_accountAddedCallback = callback;
}

int MainWindowController::getNumberOfOpenAccounts() const
{
    return m_openAccounts.size();
}

std::string MainWindowController::getFirstOpenAccountPath() const
{
    return m_openAccounts[0];
}

bool MainWindowController::isAccountOpened(const std::string& path) const
{
    return std::find(m_openAccounts.begin(), m_openAccounts.end(), path) != m_openAccounts.end();
}

AccountViewController MainWindowController::createAccountViewControllerForLatestAccount() const
{
    return { m_openAccounts[m_openAccounts.size() - 1], m_configuration.getLocale(), m_sendToastCallback };
}

void MainWindowController::addAccount(std::string& path)
{
    if(std::filesystem::path(path).extension().empty() || std::filesystem::path(path).extension() != ".nmoney")
    {
        path += ".nmoney";
    }
    if(std::find(m_openAccounts.begin(), m_openAccounts.end(), path) == m_openAccounts.end())
    {
        m_openAccounts.push_back(path);
        m_configuration.addRecentAccount(path);
        m_configuration.save();
        m_accountAddedCallback();
    }
}

void MainWindowController::closeAccount(int index)
{
    m_openAccounts.erase(m_openAccounts.begin() + index);
}
