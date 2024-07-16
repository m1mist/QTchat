/**
  ******************************************************************************
  * @file           : global.h
  * @author         : 16649
  * @brief          : None
  * @attention      : None
  * @date           : 24-7-16
  ******************************************************************************
 **/

#ifndef LLFCCHAT_GLOBAL_H
#define LLFCCHAT_GLOBAL_H
#include <QWidget>
#include <functional>
#include "QStyle"
#include <QRegularExpression>
/**
 * @brief repolish 用于刷新qss
 */
extern std::function<void(QWidget*)> repolish;

#endif //LLFCCHAT_GLOBAL_H
